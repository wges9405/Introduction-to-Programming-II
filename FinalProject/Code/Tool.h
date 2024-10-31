#ifndef TOOL_H_INCLUDED
#define TOOL_H_INCLUDED

class Tool
{
public:
    Tool();
    ~Tool();

    void Draw();

private:
    int pos_x, pos_y;
};
#endif // TOOL_H_INCLUDED
