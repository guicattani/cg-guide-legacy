template<typename T>
T lerp(float t, T a, T b)
{
    return a + t*(b-a);
}

template<typename T>
T bezier3(float t, T a, T b, T c, T d)
{
    T ab = lerp(t, a,b);
    T bc = lerp(t, b,c);
    T cd = lerp(t, c,d);
    T abc = lerp(t, ab,bc);
    T bcd = lerp(t, bc,cd);
    T abcd = lerp(t, abc,bcd);
    return abcd;
}
