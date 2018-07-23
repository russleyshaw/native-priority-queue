#ifndef _RSTD_HPP_INCLUDED_
#define _RSTD_HPP_INCLUDED_

#ifndef NDEBUG
#define RSTD_NDEBUG true
#define RSTD_LOGD(msg) std::cerr << "debug - " << msg << "\n";
#define RSTD_LOGW(msg) std::cerr << "warn - " << msg << "\n";
#define RSTD_LOGE(msg) std::cerr << "error - " << msg << "\n";
#else
#define RSTD_NDEBUG false
#define RSTD_LOGD(msg)
#define RSTD_LOGW(msg)
#define RSTD_LOGE(msg)
#endif

#endif