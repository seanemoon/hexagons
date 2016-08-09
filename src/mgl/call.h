#ifndef MGL_ERROR_H_
#define MGL_ERROR_H_

#include <string>

#define __MGL_DEBUG__

#ifdef __MGL_DEBUG__
#define MGL_CALL(code) code; mgl::MaybePrintError(__FILE__, __FUNCTION__, __LINE__, false);
#define MGL_CALL_UNSAFE(code) code; mgl::MaybePrintError(__FILE__, __FUNCTION__, __LINE__, true);
#else
#define MGL_CALL(code) code;
#define MGL_CALL(code) code;
#endif

namespace mgl {

void MaybePrintError(
    const std::string& file, const std::string& fn, int line,
    bool skip_errors);

}  // namespace mgl

#endif  //  MGL_ERROR_H_
