//
// Created by Administrator on 2020/9/2.
//

#include "FlipChartManager.h"
#include "FlipChartController.h"

FlipChartManager::~FlipChartManager() {

}

FlipChartManager::FlipChartControllerHandle FlipChartManager::newInstance() {
    int temp = m_objectUniqueId;
    m_controllerPool.insert(std::make_pair(temp, new FlipChartController));
    m_objectUniqueId++;
    return temp;
}

void FlipChartManager::disposed(FlipChartManager::FlipChartControllerHandle handle) {
    auto target = m_controllerPool.find(handle);
    if (target == m_controllerPool.end()) {
        return;
    }
    if (target->second != nullptr) {
        target->second->dispose();
        m_controllerSet.erase(target->second);
        delete target->second;
    }
    m_controllerPool.erase(handle);

}

void FlipChartManager::disposedAll() {
    for (auto iter = m_controllerPool.begin(); iter != m_controllerPool.end();) {
        iter->second->dispose();
        m_controllerSet.erase(iter->second);
        delete iter->second;
        iter = m_controllerPool.erase(iter);
    }
}

std::string FlipChartManager::loadFlipchart(FlipChartManager::FlipChartControllerHandle handle,
                                            const std::string &flipchartFilePath) {
    auto target = m_controllerPool.find(handle);
    if (target == m_controllerPool.end() || m_tempDir.empty()) {
        return "";
    }
    m_controllerSet.insert(target->second);
    return target->second->openFlipchart(flipchartFilePath, m_tempDir);
}

std::string
FlipChartManager::loadPage(FlipChartManager::FlipChartControllerHandle handle, int pageNumber) {
    auto target = m_controllerPool.find(handle);
    if (target == m_controllerPool.end()
        || m_controllerSet.find(target->second) == m_controllerSet.end()) {
        return "";
    }

    return target->second->loadPage(pageNumber);
}

FlipChartManager::FlipChartManager()
        : m_objectUniqueId(0),
          m_logEnabled(true) {

}

void FlipChartManager::setTempDir(const std::string &tempDir) {
    m_tempDir = tempDir;
}

void FlipChartManager::setLogEnabled(bool logEnabled) {
    m_logEnabled = logEnabled;
}


