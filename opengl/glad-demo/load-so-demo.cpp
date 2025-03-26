#include <dlfcn.h>

#include <iostream>

typedef void (*FunctionPtr)();

int main() {
    // 打开动态链接库
    void* handle = dlopen("./libexample.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "无法打开动态链接库: " << dlerror() << std::endl;
        return 1;
    }

    // 清除错误信息
    dlerror();

    // 获取库中的函数指针
    FunctionPtr func = (FunctionPtr)dlsym(handle, "exampleFunction");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "无法获取符号: " << dlsym_error << std::endl;
        dlclose(handle);
        return 1;
    }

    // 调用函数
    func();

    // 关闭动态链接库
    dlclose(handle);
    return 0;
}