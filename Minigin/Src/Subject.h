#pragma once
#include "Observer.h"

namespace dae
{
	class Subject
	{
	public:
		virtual void Register(Observer* o) = 0;
		virtual void Unregister(Observer* o) = 0;
		virtual void NotifyObserver() = 0;
	};
}