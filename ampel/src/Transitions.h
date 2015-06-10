/* Generated Transition File 

 * Date: 28/05/2015 02:10:46
 * 24 transitions
 */

#ifndef TRANSITIONLIST_H_
#define TRANSITIONLIST_H_


class Transitions{
	public:
		virtual void Einschalten(void) = 0;
		virtual void is_puck_in_height_determination__band_right_slowly(void) = 0;
		virtual void keine_Bohrung__band_right_normal(void) = 0;
		virtual void mit_Bohrung__band_right_normal(void) = 0;
		virtual void last_SavedPuk_passt_zur_Reihenfolge__UEberschreibe_aktuelle_Puk_ID_mit_last_SavedPuk(void) = 0;
		virtual void requestNextPuk(void) = 0;
		virtual void kein_passender_Puk__is_startButton_pushed_(void) = 0;
		virtual void aktueller_Puk_passt_zur_Reihenfolge(void) = 0;
		virtual void Reihenfolge_passt__band_right_normal(void) = 0;
		virtual void No_more_living_Puks__band_stop(void) = 0;
		virtual void _Puk_IDs_existing_on_FiFo(void) = 0;
		virtual void get_Pucks_from_Band1_FiFo(void) = 0;
		virtual void UserInteraktion(void) = 0;
		virtual void Beiseitelegen(void) = 0;
		virtual void Band1__is_puck_running_out_(void) = 0;
		virtual void is_metal_detected(void) = 0;
		virtual void timer0__timeout_after_X_sec(void) = 0;
		virtual void after_X_secs(void) = 0;
		virtual void timer1__timeout_after_X_sec(void) = 0;
		virtual void after_X_secs_is_slide_full_(void) = 0;
		virtual void Height_was_ok__open_gate(void) = 0;
		virtual void after_X_secs__close_gate(void) = 0;
		virtual void Beiseitelegen__No(void) = 0;
		virtual void Beiseitelegen__Yes(void) = 0;
};



#endif // TRANSITIONLIST_H_
