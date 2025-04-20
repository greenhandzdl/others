#include "contact_required.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <atomic>

namespace contact {

void ContactSync::autoSave(Contact& contact) {
    // 使用类的成员变量stopFlag作为停止标志
    
    while (!stopFlag) {
        // 使用条件变量或超时机制来允许更快的响应停止信号
        std::this_thread::sleep_for(std::chrono::seconds(30)); // 使用较短的检查间隔以便更快响应停止信号
        
        // 检查自动保存标志并执行保存
        if (contact.isFlagSet(Contact::AUTOSAVE_FLAG)) {
            ContactMethod::saveAsFile(contact);
        }
    }
}

ContactSync::ContactSync(Contact& contact) {
    // 创建线程并传递联系人引用
    syncThread = std::thread(&ContactSync::autoSave, this, std::ref(contact));
    std::cout << "自动保存线程已启动" << std::endl;
}

ContactSync::~ContactSync() {
    // 设置停止标志，通知自动保存线程停止
    stopFlag = true;
    
    // 如果线程可以加入，则等待它完成
    if (syncThread.joinable()) {
        // 等待线程完成
        syncThread.join();
        std::cout << "自动保存线程已停止" << std::endl;
    }
}


} // namespace contact