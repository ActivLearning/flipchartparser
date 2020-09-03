//
// Created by Administrator on 2020/9/2.
//

#ifndef ANDROID_FLIPCHARTMANAGER_H
#define ANDROID_FLIPCHARTMANAGER_H

#include <set>
#include <string>
#include <unordered_map>

class FlipChartController;

class FlipChartManager {
public:
    typedef int FlipChartControllerHandle;
    typedef int UniqueID;
public:
    FlipChartManager();
    ~FlipChartManager();
    FlipChartControllerHandle newInstance();
    void disposed(FlipChartControllerHandle handle);
    void disposedAll();
    std::string loadFlipchart(FlipChartControllerHandle handle,const std::string& flipchartFilePath);
    std::string loadPage(FlipChartControllerHandle handle,int pageNumber);
    void setTempDir(const std::string &tempDir);
    void setLogEnabled(bool mLogEnabled);
private:
    std::unordered_map<FlipChartControllerHandle ,FlipChartController*> m_controllerPool;
    std::set<FlipChartController*> m_controllerSet;
    UniqueID m_objectUniqueId;
    std::string m_tempDir;
    bool m_logEnabled;
};


#endif //ANDROID_FLIPCHARTMANAGER_H
