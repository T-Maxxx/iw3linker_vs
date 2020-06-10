#pragma once

// A helper class to organize process of initializing global stuff and only then patching.
class CModule
{
public:
    CModule();
    virtual ~CModule();

    virtual void InitGlobals() const;
    virtual void Patch() const;
};

