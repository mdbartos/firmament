#include "peripheral_globals.h"
#if ANALOG_DELSIG_ACTIVATED
#include "analog_delsig_control.h"
#include "power.h"

float32 analog_delsig_get_reading(DeviceDict device) {
	int32 raw_reading = 0;
	float32 reading = 0;
	// flip on the ADC pin
	power_toggle(1u, device.power_term); // TODO: Is this actually needed?
	CyDelay(device.on_time);	
	// Start the ADC
	analog_delsig_adc_Wakeup();
	analog_delsig_adc_Start(); 
    // Select mux term
    analog_delsig_mux_Start();
    analog_delsig_mux_Select(device.mux_term);
	// Read the voltage
    raw_reading = analog_delsig_adc_Read32();
    if (device.analog_convert_volts){
	    reading = analog_delsig_adc_CountsTo_Volts(raw_reading);
    }
    else {
        reading = raw_reading;
    }
    reading *= device.analog_gain_numerator;
    reading /= device.analog_gain_denominator;
	// Stop the conversion
	analog_delsig_adc_Sleep();
	// flip off the ADC pin
	power_toggle(0u, device.power_term);	
    // Stop analog mux
    analog_delsig_mux_Stop();
    // Write to readings
    // For now, assume only one reading per analog sensor
    (*device.readings)[0] = reading;
	return reading;
}

#endif
/* [] END OF FILE */
