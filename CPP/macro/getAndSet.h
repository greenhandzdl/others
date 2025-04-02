#define PropertyBuilderByName(type, name, access_permission)\
    access_permission:\
        type m_##name;\
    public:\
    inline void set##name(type v) {\
        m_##name = v;\
    }\
    inline type get##name() {\
        return m_##name;\
    }\

#define PointerPropertyBuilderByName(type, name, access_permission)\
    access_permission:\
        type* m_##name;\
    public:\
        inline void set##name(type* v){\
            m_##name = v;\
        }\
        inline type* get##name(){\
            return m_##name;\
        }\
