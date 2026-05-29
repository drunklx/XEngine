#pragma once
#include "XEngine/core.h"
#include "XEngine/Input.h"
namespace XEngine {
	class X_API WindowsInput: public Input{
	public:

	protected:
		virtual bool IsKeyPressedImpl(int key)override;
		virtual bool IsMouseButtonPressedImpl(int button)override;
		virtual float GetMouseXImpl()override;
		virtual float GetMouseYImpl()override;
		virtual std::pair<float, float>GetMousePositionImpl()override;
	};
}