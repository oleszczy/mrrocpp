#if !defined(_ECP_T_PLAYERJOY_IRP6OT_H)
#define _ECP_T_PLAYERJOY_IRP6OT_H

#include "ecp/common/ecp_task.h"

namespace mrrocpp {
namespace ecp {
namespace common {

class ecp_task_playerjoy_irp6ot: public ecp_task  {
protected:
	playerjoy_generator* pjg;

public:
	// KONSTRUKTORY
	ecp_task_playerjoy_irp6ot(configurator &_config);

	// methods for ECP template to redefine in concrete classes
	void task_initialization(void);
	void main_task_algorithm(void);
};

} // namespace common
} // namespace ecp
} // namespace mrrocpp

#endif
