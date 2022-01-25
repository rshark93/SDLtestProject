#pragma once

#include "WidgetContainer.h"

class Widget : public WidgetContainer {
private:
    std::string id;
protected:
public:
    Widget();
    virtual ~Widget();

    void GetWidget(std::string img2) {

    }

    void OnMouseEnter(Widget* widget) {
        widget->GetWidgetContainer();// GetWidget(img2)->Show();
    }

    /*virtual void SetId(const std::string& id) = 0;
    virtual void SetOrder(int order) = 0;
    virtual void SetPos(float x, float y) = 0;
    virtual void OnPressLMouseButton(void) = 0;
    virtual void OnReleaseLMouseButton(void) = 0;
    virtual void OnEnterLMouseButton(void) = 0;
    virtual void OnLeaveLMouseButton(void) = 0;
    virtual bool Update(float dt) = 0;
    virtual void Render(void) = 0;
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void AddEventHandler() = 0;*/
};