#pragma once
#include <stdexcept>

#if _WIN32
#define __PRETTY_FUNCTION__     __FUNCSIG__
#endif


namespace ecs {

    enum class ERROR : int {
        // EntityManager -1000 - -1100
        ENTITY_MAX_COUNT=-1000,
        ENTITY_OUT_OF_RANGE = -1001,
        ENTITY_NOT_EXISTING = -1002,

        // ComponentArray -1101 - -1200
        COMPONENT_INDEX_ERROR = -1101
    };

    class Exception : public std::exception {
    private:
        const char* msg_;
        const char* file_;
        int line_;
        const char* info_;
        int error_code_;
    public:
        Exception(
            const char* msg,
            const char* file,
            int line,
            int error_code,
            const char* info = ""
        ) : std::exception(),
            msg_(msg),
            file_(file),
            line_(line),
            info_(info),
            error_code_(error_code) {}

        const char* GetFile() const { return file_; }
        const char* GetInfo() const { return info_; }
        int GetLine() const { return line_; }
        int GetErrorCode() const { return error_code_; }
        const char* what() const noexcept override { return msg_; }
    };
}