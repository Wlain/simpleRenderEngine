//
// Created by cwb on 2022/7/25.
//

#ifndef GRAPHICRENDERENGINE_EFFECTMANAGER_H
#define GRAPHICRENDERENGINE_EFFECTMANAGER_H
#include "commonInterface.h"

class EffectManager
{
public:
    EffectManager();
    ~EffectManager();
    void insertEffect(const std::shared_ptr<CommonInterface>& effect);
    inline std::vector<std::shared_ptr<CommonInterface>>& effects() { return m_effects; }

private:
    std::vector<std::shared_ptr<CommonInterface>> m_effects;
};

#endif // GRAPHICRENDERENGINE_EFFECTMANAGER_H
