#include "Transform.h"

namespace kiko {
	void Transform::Read(const json_t& value) {

		READ_DATA_REQUIRED(value, position);
		READ_DATA_REQUIRED(value, rotation);
		READ_DATA_REQUIRED(value, scale);
	}

}
