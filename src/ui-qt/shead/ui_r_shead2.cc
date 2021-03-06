/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.01  */

#include "ui_r_shead2.h"
#include "ui_ecp_r_shead2.h"

namespace mrrocpp {
namespace ui {
namespace shead2 {

UiRobot::UiRobot(common::Interface& _interface) :
	shead::UiRobot(_interface, lib::shead2::ROBOT_NAME)
{
	add_wgt <wgt_shead_command>(shead::WGT_SHEAD_COMMAND, "Shead2 command");
}

void UiRobot::create_ui_ecp_robot()
{
	common::UiRobot::ui_ecp_robot = ui_ecp_robot = new EcpRobot(*this);

}

void UiRobot::setup_menubar()
{
	shead::UiRobot::setup_menubar();
	robot_menu->setTitle(QApplication::translate("MainWindow", "S&head2", 0, QApplication::UnicodeUTF8));
}


}
} //namespace ui
} //namespace mrrocpp

