/*!
 * @file kinematic_model_irp6ot_tfg.h
 * @brief File containing the IRp-6ot two fingered gripper kinematic model class.
 *
 * @author yoyek
 * @author tkornuta
 * @date Jun 21, 2010
 *
 * @ingroup KINEMATICS,IRP6OT_KINEMATICS
 */


#if !defined(_IRP6OT_TFG_KIN_MODEL)
#define _IRP6OT_TFG_KIN_MODEL

#include "robot/irp6_tfg/kinematic_model_irp6_tfg.h"

namespace mrrocpp {
namespace kinematics {
namespace irp6ot_tfg {

/*!
 * @class model
 * @brief Kinematic model for two fingered gripper of Ithe Rp-6 on track manipulator.
 *
 * @author tkornuta
 * @date Jun 21, 2010
 *
 * @ingroup KINEMATICS,IRP6OT_KINEMATICS
 */
class model: public common::kinematic_model_irp6_tfg
{
protected:

	//! Method responsible for kinematic parameters setting.
	void set_kinematic_parameters(void);

public:
	//! Constructor.
	model(void);

};//: kinematic_model_conveyor;

} // namespace irp6ot_tfg
} // namespace kinematic
} // namespace mrrocpp

#endif
