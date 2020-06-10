#pragma once

namespace my {

	template<class T>
	class pid;

	template<class T>
	struct pid_pos
	{
		T kp;
		T ki;
		T kd;
		T deadband;
		T integral;
		T i_threshold;
		T error_last;

	public:

		explicit pid_pos(T kp_, T ki_, T kd_, T deadband_) :
			kp(kp_),
			ki(ki_),
			kd(ki_),
			deadband(deadband_),
			integral(0),
			i_threshold(0),
			error_last(0) {
		}

	};

	template<class T>
	class pid
	{

		T abs_t(T& t) {
			return t >= 0 ? t : -t;
		}

	public:
		T out(const T& target_, const T& feedback_, my::pid_pos<T>& pid_) {
			T error = target_ - feedback_;
			if (abs_t(error) <= pid_.deadband) {
				return 0;
			}
			if (pid_.integral <= pid_.i_threshold) {
				pid_.integral += error;
			}
			T result = pid_.kp * error + pid_.ki * pid_.integral + pid_.kd * (error - pid_.error_last);
			pid_.error_last = error;
			return result;
		}

		T operator() (const T& target_, const T& feedback_, my::pid_pos<T>& pid_) {
			return this->out(target_, feedback_, pid_);
		}
	};


}
