// ------------------------------------------------------------------------
// Proces:		UI
// Plik:			ui_init.cc
// System:	QNX/MRROC++  v. 6.3
// Opis:
// Autor:		twiniarski/ ostatnie zmiany tkornuta
// Data:		14.03.2006
// ------------------------------------------------------------------------

/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.01  */

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#include <string.h>
#include <signal.h>
#include <dirent.h>

#include <sys/dispatch.h>


#include <fcntl.h>
#include <string.h>
#include <process.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <iostream>
#include <fstream>

#include <pthread.h>
#include <errno.h>

#include "lib/mis_fun.h"
#include "lib/srlib.h"
#include "ui/ui_const.h"
#include "ui/ui.h"
#include "lib/configurator.h"
#include "lib/mis_fun.h"
#include "ui/ui_ecp.h"

#include "lib/messip/messip.h"

/* Local headers */
#include "ablibs.h"
#include "abimport.h"
#include "proto.h"
#include <Pt.h>
#include <Ph.h>


lib::configurator* config;

ui_state_def ui_state;

std::ofstream *log_file_outfile;



int init( PtWidget_t *link_instance, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

{
	/* eliminate 'unreferenced' warnings */
	link_instance = link_instance, apinfo = apinfo, cbinfo = cbinfo;

	set_ui_state_notification(UI_N_STARTING);

	struct utsname sysinfo;
	char* cwd;
	char buff[PATH_MAX + 1];

	signal( SIGINT, &catch_signal );// by y aby uniemozliwic niekontrolowane zakonczenie aplikacji ctrl-c z kalwiatury
	signal( SIGALRM, &catch_signal );
	signal( SIGSEGV, &catch_signal );
#ifdef PROCESS_SPAWN_RSH
	signal( SIGCHLD, &catch_signal );
#endif /* PROCESS_SPAWN_RSH */

	lib::set_thread_priority(pthread_self() , MAX_PRIORITY-6);

	config = NULL;

	ui_state.ui_state=1;// ui working

	ui_state.irp6_on_track.edp.state=-1; // edp nieaktywne
	ui_state.irp6_on_track.edp.last_state=-1; // edp nieaktywne
	ui_state.irp6_on_track.ecp.trigger_fd = -1;
	ui_state.irp6_on_track.edp.section_name = EDP_IRP6_ON_TRACK_SECTION;
	ui_state.irp6_on_track.ecp.section_name = ECP_IRP6_ON_TRACK_SECTION;
	ui_state.irp6_postument.edp.state=-1; // edp nieaktywne
	ui_state.irp6_postument.edp.last_state=-1; // edp nieaktywne
	ui_state.irp6_postument.ecp.trigger_fd = -1;
	ui_state.irp6_postument.edp.section_name = EDP_IRP6_POSTUMENT_SECTION;
	ui_state.irp6_postument.ecp.section_name = ECP_IRP6_POSTUMENT_SECTION;
	ui_state.speaker.edp.state=-1; // edp nieaktywne
	ui_state.speaker.edp.last_state=-1; // edp nieaktywne
	ui_state.speaker.ecp.trigger_fd = -1;
	ui_state.speaker.edp.section_name = EDP_SPEAKER_SECTION;
	ui_state.speaker.ecp.section_name = ECP_SPEAKER_SECTION;
	ui_state.conveyor.edp.state=-1; // edp nieaktywne
	ui_state.conveyor.edp.last_state=-1; // edp nieaktywne
	ui_state.conveyor.ecp.trigger_fd = -1;
	ui_state.conveyor.edp.section_name = EDP_CONVEYOR_SECTION;
	ui_state.conveyor.ecp.section_name = ECP_CONVEYOR_SECTION;
	ui_state.irp6_mechatronika.edp.state=-1; // edp nieaktywne
	ui_state.irp6_mechatronika.edp.last_state=-1; // edp nieaktywne
	ui_state.irp6_mechatronika.ecp.trigger_fd = -1;
	ui_state.irp6_mechatronika.edp.section_name = EDP_IRP6_MECHATRONIKA_SECTION;
	ui_state.irp6_mechatronika.ecp.section_name = ECP_IRP6_MECHATRONIKA_SECTION;

	ui_state.file_window_mode=FSTRAJECTORY; // uczenie
	ui_state.all_edps = UI_ALL_EDPS_NONE_EDP_LOADED;
	ui_state.mp.state = UI_MP_NOT_PERMITED_TO_RUN;// mp wylaczone
	ui_state.mp.last_state= UI_MP_NOT_PERMITED_TO_RUN ;// mp wylaczone
	ui_state.mp.pid = -1;
	ui_state.is_task_window_open=false;// informacja czy okno zadanai jest otwarte
	ui_state.is_process_control_window_open=false;// informacja czy okno sterowania procesami jest otwarte
	ui_state.process_control_window_renew = true;
	ui_state.is_file_selection_window_open=false;
	ui_state.is_wind_irp6ot_int_open=false;
	ui_state.is_wind_irp6p_int_open=false;
	ui_state.is_wind_irp6m_int_open=false;
	ui_state.is_wind_polycrank_int_open=false;
	ui_state.is_wind_irp6ot_inc_open=false;
	ui_state.is_wind_irp6p_inc_open=false;
	ui_state.is_wind_irp6m_inc_open=false;
	ui_state.is_wind_polycrank_inc_open=false;
	ui_state.is_wind_irp6ot_xyz_euler_zyz_open=false;
	ui_state.is_wind_irp6p_xyz_euler_zyz_open=false;
	ui_state.is_wind_irp6m_xyz_euler_zyz_open=false;
	ui_state.is_wind_irp6ot_xyz_angle_axis_open=false;
	ui_state.is_wind_irp6p_xyz_angle_axis_open=false;
	ui_state.is_wind_irp6m_xyz_angle_axis_open=false;
	ui_state.is_wind_irp6ot_xyz_angle_axis_ts_open=false;
	ui_state.is_wind_irp6p_xyz_angle_axis_ts_open=false;
	ui_state.is_wind_irp6m_xyz_angle_axis_ts_open=false;
	ui_state.is_wind_irp6ot_xyz_euler_zyz_ts_open=false;
	ui_state.is_wind_irp6p_xyz_euler_zyz_ts_open=false;
	ui_state.is_wind_irp6m_xyz_euler_zyz_ts_open=false;
	ui_state.is_teaching_window_open=false;
	ui_state.is_wind_conveyor_moves_open=false;
	ui_state.is_wind_irp6ot_kinematic_open=false;
	ui_state.is_wind_irp6p_kinematic_open=false;
	ui_state.is_wind_irp6m_kinematic_open=false;
	ui_state.is_wind_speaker_play_open=false;

	ui_state.is_wind_irp6ot_xyz_aa_relative_open=false;
	ui_state.is_wind_irp6p_xyz_aa_relative_open=false;

	ui_state.is_wind_irp6ot_servo_algorithm_open=false;
	ui_state.is_wind_irp6p_servo_algorithm_open=false;
	ui_state.is_wind_irp6m_servo_algorithm_open=false;
	ui_state.is_wind_conv_servo_algorithm_open=false;

	ui_state.is_mp_and_ecps_active = false;
	// ui_state.is_any_edp_active = false;


	ui_state.irp6_on_track.edp.is_synchronised = false;
	ui_state.irp6_postument.edp.is_synchronised = false;
	ui_state.conveyor.edp.is_synchronised = false;
	ui_state.speaker.edp.is_synchronised = false;
	ui_state.irp6_mechatronika.edp.is_synchronised = false;

	// ustalenie katalogow UI

	if( uname( &sysinfo ) == -1 ) {
		perror( "uname" );
	}

	cwd = getcwd( buff, PATH_MAX + 1 );
	if( cwd == NULL ) {
		perror( "Blad cwd w UI" );
	}

	ui_state.ui_node_name = sysinfo.nodename;

	ui_state.binaries_local_path = cwd;
	ui_state.mrrocpp_local_path = cwd;
	ui_state.mrrocpp_local_path.erase(ui_state.mrrocpp_local_path.length()-3);// kopiowanie lokalnej sciezki bez "bin" - 3 znaki
	ui_state.binaries_network_path = "/net/";
	ui_state.binaries_network_path += ui_state.ui_node_name;
	ui_state.binaries_network_path += ui_state.binaries_local_path;
	ui_state.binaries_network_path += "/";// wysylane jako argument do procesow potomnych (mp_m i dalej)
	// printf( "system name  : %s\n", ui_state.binaries_network_path);

	// sciezka dla okna z wyborem pliku podczas wybor trajektorii dla uczenia
	ui_state.teach_filesel_fullpath = "/net/";
	ui_state.teach_filesel_fullpath += ui_state.ui_node_name;
	ui_state.teach_filesel_fullpath += ui_state.mrrocpp_local_path;
	ui_state.teach_filesel_fullpath += "trj";
	// 	printf("abba: %s\n", ui_state.teach_filesel_fullpath);

	// sciezka dla okna z wyborem pliku z trajektoria podczas wyboru pliku konfiguracyjnego
	ui_state.config_file_fullpath = "/net/";
	ui_state.config_file_fullpath += ui_state.ui_node_name;
	ui_state.config_file_fullpath += ui_state.mrrocpp_local_path;
	ui_state.config_file_fullpath += "configs";

	// printf ("Remember to create gns server\n");

	// pierwsze zczytanie pliku konfiguracyjnego (aby pobrac nazwy dla pozostalych watkow UI)
	if (get_default_configuration_file_name()>=1) // zczytaj nazwe pliku konfiguracyjnego
	{
		initiate_configuration();
		// sprawdza czy sa postawione gns's i ew. stawia je
		// uwaga serwer musi byc wczesniej postawiony
		check_gns();
	} else {
		printf ("Blad manage_default_configuration_file\n");
		PtExit( EXIT_SUCCESS );
	}


	create_threads();



	// Zablokowanie domyslnej obslugi sygnalu SIGINT w watkach UI_SR i UI_COMM


	// kolejne zczytanie pliku konfiguracyjnego
	if (get_default_configuration_file_name()==1) // zczytaj nazwe pliku konfiguracyjnego
	{
		reload_whole_configuration();

	} else {
		printf ("Blad manage_default_configuration_file\n");
		PtExit( EXIT_SUCCESS );
	}

	// inicjacja pliku z logami sr

	time_t time_of_day;
	char file_date[50];
	char log_file_with_dir[100];
	char file_name[50];

	time_of_day = time( NULL );
	strftime( file_date, 40, "%g%m%d_%H-%M-%S", localtime( &time_of_day ) );

	sprintf(file_name,"/%s_sr_log", file_date);

	// 	strcpy(file_name,"/pomiar.p");
	strcpy(log_file_with_dir, "../logs/");
	strcat(log_file_with_dir, file_name);

	log_file_outfile = new std::ofstream(log_file_with_dir, std::ios::out);

	if (!(*log_file_outfile)) {
		std::cerr << "Cannot open file: " << file_name << '\n';
		perror("because of");
	}

	manage_interface();

	return( Pt_CONTINUE );

}
