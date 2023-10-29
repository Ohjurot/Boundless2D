#include "IoCStack.h"

bl2d::IoCStack::~IoCStack()
{
    Clear();
}

void* bl2d::IoCStack::GetPtr(std::type_index type, std::string_view name /*= ""*/)
{
    // First on parent than local
    void* instance = m_parent ? m_parent->GetPtr(type, name) : nullptr;
    if (!instance)
    {
        // Find instance
        auto itBin = m_apiToStack.find(type);
        if (itBin != m_apiToStack.end())
        {
            auto& bin = itBin->second;
            auto itElement = bin.find(std::string(name));
            if (itElement != bin.end())
            {
                instance = itElement->second->instance;
            }
        }

        // Create instance
        if (!instance)
        {
            auto* element = Push(type, name);
            if (element)
            {
                instance = element->instance;
            }
        }
    }

    return instance;
}

void bl2d::IoCStack::Clear()
{
    while (!m_stack.empty())
    {
        auto& element = m_stack.back();
        element.descriptor.dTor(element.instance);
        free(element.instance);

        m_stack.pop_back();
    }

    m_apiToStack.clear();
}

bl2d::IoCStack::StackElement* bl2d::IoCStack::Push(std::type_index type, std::string_view name /*= ""*/)
{
    auto* desc = IoCRegistrations::Get().Lookup(type, name);
    if (desc)
    {
        // Create instance
        StackElement element;
        element.descriptor = *desc;
        element.instance = malloc(element.descriptor.objectSize);
        element.descriptor.cTor(element.instance, *this);
        
        // Storing the instance
        m_stack.push_back(std::move(element));
        auto* ptr = &m_stack.back();
        m_apiToStack[type][std::string(name)] = ptr;
        return ptr;
    }

    return nullptr;
}
