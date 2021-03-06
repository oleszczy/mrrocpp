/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.01  */

#include "ui_r_smb1.h"
#include "ui_ecp_r_smb1.h"

namespace mrrocpp {
namespace ui {
namespace smb1 {

UiRobot::UiRobot(common::Interface& _interface) :
		smb::UiRobot(_interface, lib::smb1::ROBOT_NAME)
{
	add_wgt <wgt_smb_command>(smb::WGT_SMB_COMMAND, "Smb1 command");
}

void UiRobot::create_ui_ecp_robot()
{
	common::UiRobot::ui_ecp_robot = ui_ecp_robot = new EcpRobot(*this);
}

void UiRobot::setup_menubar()
{
	smb::UiRobot::setup_menubar();
	robot_menu->setTitle(QApplication::translate("MainWindow", "S&mb1", 0, QApplication::UnicodeUTF8));
}

}
} //namespace ui
} //namespace mrrocpp

