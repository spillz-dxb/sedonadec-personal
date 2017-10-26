/**************************************************************************
*
* Copyright (C) 2005 Steve Karg <skarg@users.sourceforge.net>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*********************************************************************/

/* Analog Output Objects - customize for your use */

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "bacdef.h"
#include "bacdcode.h"
#include "bacenum.h"
#include "bacapp.h"
#include "config.h"     /* the custom stuff */
#include "wp.h"
#include "ao.h"
#include "handlers.h"

#include "sedona.h"

#include <math.h>

#ifndef MAX_ANALOG_OUTPUTS
#define MAX_ANALOG_OUTPUTS 4
#endif

struct pwm_def{
	int chip_id;
	int pwm_no;
};

static struct pwm_def pwm_arr[] = {

	{
		.chip_id = 0, //AO_0 -> Dummy
		.pwm_no = 0,	
	},

	{
		.chip_id = 2, //AO_1 -> P9_16
		.pwm_no = 1,				
	},

	{
		.chip_id = 2, //AO_2 -> P9_14
		.pwm_no = 0,				
	},

	{
		.chip_id = 6, //AO_3 -> P9_42
		.pwm_no = 0,				
	},

	{
		.chip_id = 4, //AO_4 -> P8_13
		.pwm_no = 1,				
	},

	{
		.chip_id = 4, //AO_5 -> P8_19
		.pwm_no = 0,				
	},
};


unsigned long period_val = 1000000000;
unsigned long duty_cycle_val = 500000000;
char export[100];
char period[100];
char dutycycle[100];
char enable[100];
int chip_id = 0;
int pwm_no = 0;
int enable_val = 0;

volatile static float level2_ao = 0.0;
static float level2_ao_new = 0.0;
static bool priority_change_ao = false;
static unsigned int override_en_ao = 0; //tell you override status from BDT
static unsigned int override_en_bkp_ao = 0; //tell you override status from BDT
volatile static unsigned int priority_sae_ao = 0; //new pri level which is modified by sedona
volatile static unsigned int priority_bkp_ao = 0; // pri level comes from sedona (so taking backup for the next step)
volatile static unsigned int priority_act_ao = 255; //default value

static int ov_instance = -1;

//make it global
unsigned int object_index = 0;
unsigned int priority = 0;

static unsigned int dummy_ao = 0;
static unsigned int dummy_ao2 = 0;

volatile static int pri_array[MAX_ANALOG_OUTPUTS];

/* we choose to have a NULL level in our system represented by */
/* a particular value.  When the priorities are not in use, they */
/* will be relinquished (i.e. set to the NULL level). */
#define AO_LEVEL_NULL 255
/* When all the priorities are level null, the present value returns */
/* the Relinquish Default value */
#define AO_RELINQUISH_DEFAULT 0
/* Here is our Priority Array.  They are supposed to be Real, but */
/* we don't have that kind of memory, so we will use a single byte */
/* and load a Real for returning the value when asked. */

static float Analog_Output_Level[MAX_ANALOG_OUTPUTS][BACNET_MAX_PRIORITY];


/* Writable out-of-service allows others to play with our Present Value */
/* without changing the physical output */
static bool Analog_Output_Out_Of_Service[MAX_ANALOG_OUTPUTS];

/* we need to have our arrays initialized before answering any calls */
static bool Analog_Output_Initialized = false;

/* These three arrays are used by the ReadPropertyMultiple handler */
static const int Properties_Required[] = {
    PROP_OBJECT_IDENTIFIER,
    PROP_OBJECT_NAME,
    PROP_OBJECT_TYPE,
    PROP_PRESENT_VALUE,
    PROP_STATUS_FLAGS,
    PROP_EVENT_STATE,
    PROP_OUT_OF_SERVICE,
    PROP_UNITS,
    PROP_PRIORITY_ARRAY,
    PROP_RELINQUISH_DEFAULT,
    -1
};

static const int Properties_Optional[] = {
    -1
};

static const int Properties_Proprietary[] = {
    -1
};

void Analog_Output_Property_Lists(
    const int **pRequired,
    const int **pOptional,
    const int **pProprietary)
{
    if (pRequired)
        *pRequired = Properties_Required;
    if (pOptional)
        *pOptional = Properties_Optional;
    if (pProprietary)
        *pProprietary = Properties_Proprietary;

    return;
}

void Analog_Output_Init(
    void)
{
    unsigned i, j;
    int ret = 0;

    if (!Analog_Output_Initialized) {
        Analog_Output_Initialized = true;

	system("config-pin overlay cape-universal");
	system("echo am33xx_pwm > /sys/devices/platform/bone_capemgr/slots");

        /* initialize all the analog output priority arrays to NULL */
        for (i = 0; i < MAX_ANALOG_OUTPUTS; i++) {

		switch (i) {
			case 2:
				ret = system("config-pin P9.14 gpio");
				if (ret != 0)
					printf("Writing pinmux failed for P9.14\n");

				ret = system("config-pin P9.14 pwm");
				if (ret != 0)
					printf("Writing pinmux failed for P9.14\n");

				break;
			case 1:
				ret = system("config-pin P9.16 gpio");
				if (ret != 0)
					printf("Writing pinmux failed for P9.16\n");


				ret = system("config-pin P9.16 pwm");
				if (ret != 0)
					printf("Writing pinmux failed for P9.16\n");

				break;
			case 5:
				ret = system("config-pin P8.19 gpio");
				if (ret != 0)
					printf("Writing pinmux failed for P8.19\n");

				ret = system("config-pin P8.19 pwm");
				if (ret != 0)
					printf("Writing pinmux failed for P8.19\n");
				break;
			case 4:
				ret = system("config-pin P8.13 gpio");
				if (ret != 0)
					printf("Writing pinmux failed for P8.13\n");


				ret = system("config-pin P8.13 pwm");
				if (ret != 0)
					printf("Writing pinmux failed for P8.13\n");
				break;
			case 3:
				ret = system("config-pin P9.42 gpio");
				if (ret != 0)
					printf("Writing pinmux failed for P9.42\n");


				ret = system("config-pin P9.42 pwm");
				if (ret != 0)
					printf("Writing pinmux failed for P9.42\n");
				break;
			default:
				printf("default case Analog_Output_Init\n");

		}

	if (i == 0)//Ignore the first entry
		goto exit;

	sprintf(export, "echo %d > /sys/class/pwm/pwmchip%d/export",pwm_arr[i].pwm_no,pwm_arr[i].chip_id);
	ret = system(export);

	sprintf(enable, "echo %d > /sys/class/pwm/pwmchip%d/pwm%d/enable", 1, pwm_arr[i].chip_id, pwm_arr[i].pwm_no);
	ret = system(enable);

	sprintf(period, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/period", 0, pwm_arr[i].chip_id, pwm_arr[i].pwm_no);
	ret = system(period);

	sprintf(dutycycle, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/duty_cycle", 0, pwm_arr[i].chip_id, pwm_arr[i].pwm_no);
	ret = system(dutycycle);

exit:
            for (j = 0; j < BACNET_MAX_PRIORITY; j++) {
                Analog_Output_Level[i][j] = AO_LEVEL_NULL;
            }
        }
    }

    return;
}

/* we simply have 0-n object instances.  Yours might be */
/* more complex, and then you need validate that the */
/* given instance exists */
bool Analog_Output_Valid_Instance(
    uint32_t object_instance)
{
    if (object_instance < MAX_ANALOG_OUTPUTS)
        return true;

    return false;
}

/* we simply have 0-n object instances.  Yours might be */
/* more complex, and then count how many you have */
unsigned Analog_Output_Count(
    void)
{
    return MAX_ANALOG_OUTPUTS;
}

/* we simply have 0-n object instances.  Yours might be */
/* more complex, and then you need to return the instance */
/* that correlates to the correct index */
uint32_t Analog_Output_Index_To_Instance(
    unsigned index)
{
    return index;
}

/* we simply have 0-n object instances.  Yours might be */
/* more complex, and then you need to return the index */
/* that correlates to the correct instance number */
unsigned Analog_Output_Instance_To_Index(
    uint32_t object_instance)
{
    unsigned index = MAX_ANALOG_OUTPUTS;

    if (object_instance < MAX_ANALOG_OUTPUTS)
        index = object_instance;

    return index;
}

float Analog_Output_Present_Value(
    uint32_t object_instance)
{
    float value = AO_RELINQUISH_DEFAULT;
    unsigned index = 0;
    unsigned i = 0;

    index = Analog_Output_Instance_To_Index(object_instance);
    if (index < MAX_ANALOG_OUTPUTS) {
        for (i = 0; i < BACNET_MAX_PRIORITY; i++) {
            if (Analog_Output_Level[index][i] != AO_LEVEL_NULL) {
                value = Analog_Output_Level[index][i];
                break;
            }
        }
    }
//Updating the float value and priority which are going to send to sedona.
	level2_ao = value;
	priority_act_ao = i;
	return value;
}

unsigned Analog_Output_Present_Value_Priority(
    uint32_t object_instance)
{
    unsigned index = 0; /* instance to index conversion */
    unsigned i = 0;     /* loop counter */
    unsigned priority = 0;      /* return value */

    index = Analog_Output_Instance_To_Index(object_instance);
    if (index < MAX_ANALOG_OUTPUTS) {
        for (i = 0; i < BACNET_MAX_PRIORITY; i++) {
            if (Analog_Output_Level[index][i] != AO_LEVEL_NULL) {
                priority = i + 1;
                break;
            }
        }
    }

    return priority;
}

bool Analog_Output_Present_Value_Set(
    uint32_t object_instance,
    float value,
    unsigned priority)
{
    unsigned index = 0;
    bool status = false;
    float percentage;
    int ret = 0;
	unsigned long period_ns = 0;
	unsigned long freq = 2000;
	float duty = 0.0;

    index = Analog_Output_Instance_To_Index(object_instance);
    if (index < MAX_ANALOG_OUTPUTS) {
        if (priority && (priority <= BACNET_MAX_PRIORITY) &&
            (priority != 6 /* reserved */ ) &&
            (value >= 0.0) && (value <= 100.0)) {
			Analog_Output_Level[index][priority - 1] = value;

			duty = value / 10;

			period_ns = round(1.0e9 / freq);
			duty = round( period_ns * duty );
			unsigned long duty_ns_int = (unsigned long) duty;

			printf("period_ns %ld, duty_ns_int %ld \n",period_ns,duty_ns_int);

			if (index == 0)//Ignore the first entry
				goto exit;

			sprintf(period, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/period", period_ns, pwm_arr[index].chip_id, pwm_arr[index].pwm_no);
			ret = system(period);

			if (ret != 0)
				printf("%s:%d Writing period failed\n", __func__, __LINE__);

			sprintf(dutycycle, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/duty_cycle", duty_ns_int, pwm_arr[index].chip_id, pwm_arr[index].pwm_no);
			ret = system(dutycycle);

			if (ret != 0)
				printf("%s:%d Writing dutycycle failed\n", __func__, __LINE__);

exit:
            /* Note: you could set the physical output here to the next
               highest priority, or to the relinquish default if no
               priorities are set.
               However, if Out of Service is TRUE, then don't set the
               physical output.  This comment may apply to the
               main loop (i.e. check out of service before changing output) */
            status = true;
        }
    }

    return status;
}

bool Analog_Output_Present_Value_Relinquish(
    uint32_t object_instance,
    unsigned priority)
{
    unsigned index = 0;
    bool status = false;
    int ret = 0;

    index = Analog_Output_Instance_To_Index(object_instance);
    if (index < MAX_ANALOG_OUTPUTS) {
        if (priority && (priority <= BACNET_MAX_PRIORITY) &&
            (priority != 6 /* reserved */ )) {
            Analog_Output_Level[index][priority - 1] = AO_LEVEL_NULL; 
            /* Note: you could set the physical output here to the next
               highest priority, or to the relinquish default if no
               priorities are set.
               However, if Out of Service is TRUE, then don't set the
               physical output.  This comment may apply to the
               main loop (i.e. check out of service before changing output) */
            status = true;

		if (index == 0)//Ignore the first entry
			goto exit;

		sprintf(period, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/period", 0, pwm_arr[index].chip_id, pwm_arr[index].pwm_no);
		ret = system(period);

		if (ret != 0)
			printf("%s:%d Writing period failed\n", __func__, __LINE__);

		sprintf(dutycycle, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/duty_cycle", 0, pwm_arr[index].chip_id, pwm_arr[index].pwm_no);
		ret = system(dutycycle);

		if (ret != 0)
			printf("%s:%d Writing dutycycle failed\n", __func__, __LINE__);

exit:
		printf("\n");
        }
    }

    return status;
}

/* note: the object name must be unique within this device */
bool Analog_Output_Object_Name(
    uint32_t object_instance,
    BACNET_CHARACTER_STRING * object_name)
{
    static char text_string[32] = "";   /* okay for single thread */
    bool status = false;

    if (object_instance < MAX_ANALOG_OUTPUTS) {
        sprintf(text_string, "ANALOG OUTPUT %lu",
            (unsigned long) object_instance);
        status = characterstring_init_ansi(object_name, text_string);
    }

    return status;
}

/* return apdu len, or BACNET_STATUS_ERROR on error */
int Analog_Output_Read_Property(
    BACNET_READ_PROPERTY_DATA * rpdata)
{

    int len = 0;
    int apdu_len = 0;   /* return value */
    BACNET_BIT_STRING bit_string;
    BACNET_CHARACTER_STRING char_string;
    float real_value = (float) 1.414;
    unsigned object_index = 0;
    unsigned i = 0;
    bool state = false;
    uint8_t *apdu = NULL;

    if ((rpdata == NULL) || (rpdata->application_data == NULL) ||
        (rpdata->application_data_len == 0)) {
        return 0;
    }
    apdu = rpdata->application_data;
    switch (rpdata->object_property) {
        case PROP_OBJECT_IDENTIFIER:
            apdu_len =
                encode_application_object_id(&apdu[0], OBJECT_ANALOG_OUTPUT,
                rpdata->object_instance);
            break;
        case PROP_OBJECT_NAME:
        case PROP_DESCRIPTION:
            Analog_Output_Object_Name(rpdata->object_instance, &char_string);
            apdu_len =
                encode_application_character_string(&apdu[0], &char_string);
            break;
        case PROP_OBJECT_TYPE:
            apdu_len =
                encode_application_enumerated(&apdu[0], OBJECT_ANALOG_OUTPUT);
            break;
        case PROP_PRESENT_VALUE:
            real_value = Analog_Output_Present_Value(rpdata->object_instance);
            apdu_len = encode_application_real(&apdu[0], real_value);
            break;
        case PROP_STATUS_FLAGS:
            bitstring_init(&bit_string);
            bitstring_set_bit(&bit_string, STATUS_FLAG_IN_ALARM, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_FAULT, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_OVERRIDDEN, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_OUT_OF_SERVICE, false);
            apdu_len = encode_application_bitstring(&apdu[0], &bit_string);
            break;
        case PROP_EVENT_STATE:
            apdu_len =
                encode_application_enumerated(&apdu[0], EVENT_STATE_NORMAL);
            break;
        case PROP_OUT_OF_SERVICE:
            object_index =
                Analog_Output_Instance_To_Index(rpdata->object_instance);
            state = Analog_Output_Out_Of_Service[object_index];
            apdu_len = encode_application_boolean(&apdu[0], state);
            break;
        case PROP_UNITS:
            apdu_len = encode_application_enumerated(&apdu[0], UNITS_PERCENT);
            break;
        case PROP_PRIORITY_ARRAY:
            /* Array element zero is the number of elements in the array */
            if (rpdata->array_index == 0)
                apdu_len =
                    encode_application_unsigned(&apdu[0], BACNET_MAX_PRIORITY);
            /* if no index was specified, then try to encode the entire list */
            /* into one packet. */
            else if (rpdata->array_index == BACNET_ARRAY_ALL) {
                object_index =
                    Analog_Output_Instance_To_Index(rpdata->object_instance);
                for (i = 0; i < BACNET_MAX_PRIORITY; i++) {
                    /* FIXME: check if we have room before adding it to APDU */
                    if (Analog_Output_Level[object_index][i] == AO_LEVEL_NULL)
                        len = encode_application_null(&apdu[apdu_len]);
                    else {
                        real_value = Analog_Output_Level[object_index][i];
                        len =
                            encode_application_real(&apdu[apdu_len],
                            real_value);
                    }
                    /* add it if we have room */
                    if ((apdu_len + len) < MAX_APDU)
                        apdu_len += len;
                    else {
                        rpdata->error_class = ERROR_CLASS_SERVICES;
                        rpdata->error_code = ERROR_CODE_NO_SPACE_FOR_OBJECT;
                        apdu_len = BACNET_STATUS_ERROR;
                        break;
                    }
                }
            } else {
                object_index =
                    Analog_Output_Instance_To_Index(rpdata->object_instance);
                if (rpdata->array_index <= BACNET_MAX_PRIORITY) {
                    if (Analog_Output_Level[object_index][rpdata->array_index -
                            1] == AO_LEVEL_NULL)
                        apdu_len = encode_application_null(&apdu[0]);
                    else {
                        real_value = Analog_Output_Level[object_index]
                            [rpdata->array_index - 1];
                        apdu_len =
                            encode_application_real(&apdu[0], real_value);
                    }
                } else {
                    rpdata->error_class = ERROR_CLASS_PROPERTY;
                    rpdata->error_code = ERROR_CODE_INVALID_ARRAY_INDEX;
                    apdu_len = BACNET_STATUS_ERROR;
                }
            }
            break;
        case PROP_RELINQUISH_DEFAULT:
            real_value = AO_RELINQUISH_DEFAULT;
            apdu_len = encode_application_real(&apdu[0], real_value);
            break;
        default:
            rpdata->error_class = ERROR_CLASS_PROPERTY;
            rpdata->error_code = ERROR_CODE_UNKNOWN_PROPERTY;
            apdu_len = BACNET_STATUS_ERROR;
            break;
    }
    /*  only array properties can have array options */
    if ((apdu_len >= 0) && (rpdata->object_property != PROP_PRIORITY_ARRAY) &&
        (rpdata->array_index != BACNET_ARRAY_ALL)) {
        rpdata->error_class = ERROR_CLASS_PROPERTY;
        rpdata->error_code = ERROR_CODE_PROPERTY_IS_NOT_AN_ARRAY;
        apdu_len = BACNET_STATUS_ERROR;
    }

    return apdu_len;
}

/* returns true if successful */
bool Analog_Output_Write_Property(
    BACNET_WRITE_PROPERTY_DATA * wp_data)
{

    bool status = false;        /* return value */
    int len = 0,i;
    BACNET_APPLICATION_DATA_VALUE value;

    /* decode the some of the request */
    len =
        bacapp_decode_application_data(wp_data->application_data,
        wp_data->application_data_len, &value);
    /* FIXME: len < application_data_len: more data? */
    if (len < 0) {
        /* error while decoding - a value larger than we can handle */
        wp_data->error_class = ERROR_CLASS_PROPERTY;
        wp_data->error_code = ERROR_CODE_VALUE_OUT_OF_RANGE;
        return false;
    }
    /*  only array properties can have array options */
    if ((wp_data->object_property != PROP_PRIORITY_ARRAY) &&
        (wp_data->array_index != BACNET_ARRAY_ALL)) {
        wp_data->error_class = ERROR_CLASS_PROPERTY;
        wp_data->error_code = ERROR_CODE_PROPERTY_IS_NOT_AN_ARRAY;
        return false;
    }
    switch (wp_data->object_property) {
        case PROP_PRESENT_VALUE:
			if (value.tag == BACNET_APPLICATION_TAG_REAL) {
                priority = wp_data->priority;

				if (priority < pri_array[wp_data->object_instance]) {
				    /* Command priority 6 is reserved for use by Minimum On/Off
				       algorithm and may not be used for other purposes in any
				       object. */
					if (wp_data->priority != 6)
					printf("Analog_Output_Write_Property: OVERRIDE occured for instance %d!!! \n",wp_data->object_instance);

					ov_instance = wp_data->object_instance;
					override_en_ao = 1;
				}

				priority_bkp_ao = priority;
				status = true;

				if (override_en_ao == 1) {
					printf("BACnet: Analog_Output_Write_Property: Updating the value in BACnet as we received override; object_id %d priority %d Value %f\n",object_index,priority,value.type.Real);

					status =
					    Analog_Output_Present_Value_Set(wp_data->object_instance,
					    value.type.Real, wp_data->priority);
				}

                if (wp_data->priority == 6) {
                    /* Command priority 6 is reserved for use by Minimum On/Off
                       algorithm and may not be used for other purposes in any
                       object. */
                    wp_data->error_class = ERROR_CLASS_PROPERTY;
                    wp_data->error_code = ERROR_CODE_WRITE_ACCESS_DENIED;
                } else if (!status) {
                    wp_data->error_class = ERROR_CLASS_PROPERTY;
                    wp_data->error_code = ERROR_CODE_VALUE_OUT_OF_RANGE;
                }
            } else {
                status =
                    WPValidateArgType(&value, BACNET_APPLICATION_TAG_NULL,
                    &wp_data->error_class, &wp_data->error_code);
                if (status) {
                    object_index =
                        Analog_Output_Instance_To_Index
                        (wp_data->object_instance);
                    status =
                        Analog_Output_Present_Value_Relinquish
                        (wp_data->object_instance, wp_data->priority);
                    if (!status) {
                        wp_data->error_class = ERROR_CLASS_PROPERTY;
                        wp_data->error_code = ERROR_CODE_VALUE_OUT_OF_RANGE;
                    }
                }
            }

			level2_ao = Analog_Output_Present_Value(wp_data->object_instance);
            break;

        case PROP_OUT_OF_SERVICE:
            status =
                WPValidateArgType(&value, BACNET_APPLICATION_TAG_BOOLEAN,
                &wp_data->error_class, &wp_data->error_code);
            if (status) {
                object_index =
                    Analog_Output_Instance_To_Index(wp_data->object_instance);
                Analog_Output_Out_Of_Service[object_index] =
                    value.type.Boolean;
            }
            break;
        case PROP_OBJECT_IDENTIFIER:
        case PROP_OBJECT_NAME:
        case PROP_OBJECT_TYPE:
        case PROP_STATUS_FLAGS:
        case PROP_EVENT_STATE:
        case PROP_UNITS:
        case PROP_PRIORITY_ARRAY:
        case PROP_RELINQUISH_DEFAULT:
        case PROP_DESCRIPTION:
            wp_data->error_class = ERROR_CLASS_PROPERTY;
            wp_data->error_code = ERROR_CODE_WRITE_ACCESS_DENIED;
            break;
        default:
            wp_data->error_class = ERROR_CLASS_PROPERTY;
            wp_data->error_code = ERROR_CODE_UNKNOWN_PROPERTY;
            break;
    }

    return status;
}

float Analog_Output_Present_Value_Sedona(
    uint32_t object_instance)
{
    float value = AO_RELINQUISH_DEFAULT;
    unsigned index = 0;
    unsigned i = 0;
    unsigned pri = 9;

    index = Analog_Output_Instance_To_Index(object_instance);
    if (index < MAX_ANALOG_OUTPUTS) {
        for (i = 0; i < BACNET_MAX_PRIORITY; i++) {

            if (Analog_Output_Level[index][i] != AO_LEVEL_NULL) {
				pri = i;
				printf("BACnet: Analog_Output_Present_Value_Sedona: index %d Priority %d \n",index,i);
                break;
            }
        }
    }
    return pri;
}

/* return the instance or ObjectID to Sedona for which is received override event */
Cell BACnet_BACnetDev_doBacnetAOValueStatus(SedonaVM* vm, Cell* params)
{
	Cell result;
	level2_ao_new = Analog_Output_Present_Value(params[0].ival);
	result.fval = level2_ao_new;
	return result;

}

/* return the particular ObjectID current value to Sedona */
BACnet_BACnetDev_doBacnetAOOverrideInst(SedonaVM* vm, Cell* params)
{
	return ov_instance;
}


/* return the actual priority used in BDT (BACnet discovery device) tool to Sedona */
BACnet_BACnetDev_doBacnetAOPriorityStatus(SedonaVM* vm, Cell* params)
{
	priority_sae_ao = params[0].ival;
	pri_array[params[2].ival] = params[0].ival;
	return priority_act_ao;
}

/* return the override event */
BACnet_BACnetDev_doBacnetAOOverrideStatus(SedonaVM* vm, Cell* params)
{
	override_en_bkp_ao = override_en_ao;//backup the override event.
	override_en_ao = 0;//clear out override event.
	ov_instance = -1;
	return override_en_bkp_ao;
}

/* Initialize the BACnet objects and update the value in BACnet what Sedona writes */
BACnet_BACnetDev_doBacnetAOValueUpdate(SedonaVM* vm, Cell* params)
{

	object_index = params[2].ival;//getting ObjectID from Sedona

	unsigned long period_ns = 0;
	unsigned long freq = 2000;
	float duty = 0.0;
	int ret = 0;	
	duty = params[0].fval / 10;

	period_ns = round(1.0e9 / freq);
	duty = round( period_ns * duty );
	unsigned long duty_ns_int = (unsigned long) duty;

	if (dummy_ao == 0) {
		int i=0;
		printf("BACnet: BACnet_BACnetDev_doBacnetAOValueUpdate: AO initialize is done!\n");
		dummy_ao++;
		priority_act_ao = DEF_SEDONA_PRIORITY;//default priority (@10)

		for (i=0;i<MAX_ANALOG_OUTPUTS;i++)
			Analog_Output_Level[i][DEF_SEDONA_PRIORITY] = 0.0;//Init all the 5 objects

		if (object_index == 0)//Ignore the first entry
			goto exit1;

		sprintf(period, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/period", 0, pwm_arr[object_index].chip_id, pwm_arr[object_index].pwm_no);
		ret = system(period);

		if (ret != 0)
			printf("%s:%d Writing period failed\n", __func__, __LINE__);

		sprintf(dutycycle, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/duty_cycle", 0, pwm_arr[object_index].chip_id, pwm_arr[object_index].pwm_no);
		ret = system(dutycycle);

		if (ret != 0)
			printf("%s:%d Writing dutycycle failed\n", __func__, __LINE__);
exit1:
		printf("\n");
	}

	if (params[1].ival) {
		printf("BACnet_BACnetDev_doBacnetAOValueUpdate: ALERT !!! WRITING by SAE! object_index %d , priority_act %d value %f params[2].ival %d\n",object_index,priority_act_ao,params[0].fval,params[2].ival);
		Analog_Output_Level[object_index][priority_act_ao] = params[0].fval;//Float Value updating in BDT

		if (object_index == 0)//Ignore the first entry
			goto exit2;

		sprintf(period, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/period", period_ns, pwm_arr[object_index].chip_id, pwm_arr[object_index].pwm_no);
		ret = system(period);

		if (ret != 0)
			printf("%s:%d Writing period failed\n", __func__, __LINE__);

		sprintf(dutycycle, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/duty_cycle", duty_ns_int, pwm_arr[object_index].chip_id, pwm_arr[object_index].pwm_no);
		ret = system(dutycycle);

		if (ret != 0)
			printf("%s:%d Writing dutycycle failed\n", __func__, __LINE__);
exit2:
		printf("\n");
	}

}


/* Write the value again if ObjectID is changed */
BACnet_BACnetDev_doBacnetAOObjectIdUpdate(SedonaVM* vm, Cell* params)
{
	unsigned pri = 9;
	float val = 0.0;
	int ret = 0;
	unsigned long period_ns = 0;
	unsigned long freq = 2000;
	float duty = 0.0;
	
	duty = params[1].fval / 10;
	period_ns = round(1.0e9 / freq);
	duty = round( period_ns * duty );
	unsigned long duty_ns_int = (unsigned long) duty;

	pri = Analog_Output_Present_Value_Sedona(params[0].ival);
	val = Analog_Output_Present_Value(params[0].ival);

	printf("BACnet: BACnet_BACnetDev_doBacnetAOObjectIdUpdate Priority %d, ObjectID %d, Value in Sedona %f, Value in BACnet %f\n",pri,params[0].ival,params[1].fval,val);

	printf("BACnet : BACnet_BACnetDev_doBacnetAOObjectIdUpdate : Writing the value for changed ObjectID...  Priority %d, New ObjectID %d, Value %f\n",pri,params[0].ival,params[1].fval);

	if (params[0].ival == 0)//Ignore the first entry
		goto exit;

	sprintf(period, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/period", period_ns, pwm_arr[params[0].ival].chip_id, pwm_arr[params[0].ival].pwm_no);
	ret = system(period);

	if (ret != 0)
		printf("%s:%d Writing period failed\n", __func__, __LINE__);

	sprintf(dutycycle, "echo %ld > /sys/class/pwm/pwmchip%d/pwm%d/duty_cycle", duty_ns_int, pwm_arr[params[0].ival].chip_id, pwm_arr[params[0].ival].pwm_no);
	ret = system(dutycycle);

	if (ret != 0)
		printf("%s:%d Writing dutycycle failed\n", __func__, __LINE__);

exit:
	Analog_Output_Level[params[0].ival][pri] = params[1].fval;//Value updating in BDT

	return pri;
}

/* Backup the objectID */
Cell BACnet_BACnetDev_doBacnetAOObjectIdBkp(SedonaVM* vm, Cell* params)
{
	Cell val;
	val.fval = Analog_Output_Present_Value(params[0].ival);
	return val;
}


#ifdef TEST
#include <assert.h>
#include <string.h>
#include "ctest.h"

bool WPValidateArgType(
    BACNET_APPLICATION_DATA_VALUE * pValue,
    uint8_t ucExpectedTag,
    BACNET_ERROR_CLASS * pErrorClass,
    BACNET_ERROR_CODE * pErrorCode)
{
    pValue = pValue;
    ucExpectedTag = ucExpectedTag;
    pErrorClass = pErrorClass;
    pErrorCode = pErrorCode;

    return false;
}

void testAnalogOutput(
    Test * pTest)
{
    uint8_t apdu[MAX_APDU] = { 0 };
    int len = 0;
    uint32_t len_value = 0;
    uint8_t tag_number = 0;
    uint32_t decoded_instance = 0;
    uint16_t decoded_type = 0;
    BACNET_READ_PROPERTY_DATA rpdata;

    Analog_Output_Init();
    rpdata.application_data = &apdu[0];
    rpdata.application_data_len = sizeof(apdu);
    rpdata.object_type = OBJECT_ANALOG_OUTPUT;
    rpdata.object_instance = 1;
    rpdata.object_property = PROP_OBJECT_IDENTIFIER;
    rpdata.array_index = BACNET_ARRAY_ALL;
    len = Analog_Output_Read_Property(&rpdata);
    ct_test(pTest, len != 0);
    len = decode_tag_number_and_value(&apdu[0], &tag_number, &len_value);
    ct_test(pTest, tag_number == BACNET_APPLICATION_TAG_OBJECT_ID);
    len = decode_object_id(&apdu[len], &decoded_type, &decoded_instance);
    ct_test(pTest, decoded_type == rpdata.object_type);
    ct_test(pTest, decoded_instance == rpdata.object_instance);

    return;
}

#ifdef TEST_ANALOG_OUTPUT
int main(
    void)
{
    Test *pTest;
    bool rc;

    pTest = ct_create("BACnet Analog Output", NULL);
    /* individual tests */
    rc = ct_addTestFunction(pTest, testAnalogOutput);
    assert(rc);

    ct_setStream(pTest, stdout);
    ct_run(pTest);
    (void) ct_report(pTest);
    ct_destroy(pTest);

    return 0;
}
#endif /* TEST_ANALOG_INPUT */
#endif /* TEST */
