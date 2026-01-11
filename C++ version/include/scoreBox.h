#pragma once

#include <bbop/Graphics.h>

class ScoreBox : public BbopDrawable
{
private :
    Font font;
    TexteBox textScore;

public :
    ScoreBox();
    virtual ScoreBox();

    virtual void Draw(GLint* renderUniform) const override;

    void update(int value);

};