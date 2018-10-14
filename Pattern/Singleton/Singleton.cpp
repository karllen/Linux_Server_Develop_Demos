//C++03
class CSingleton
{
public:
    ~CSingleton() {}
    static CSingleton * getInstance()
    {
        if (m_instance == nullptr)
        {
            std::lock_guard<std::mutex> lgd(m_mt);
            if (m_instance == nullptr)
            {
                m_instance = new CSingleton; //maybe wrong
            }
        }
        return m_instance;
    }
    static void delInstance()
    {
        std::lock_guard<std::mutex> lgd(m_mt);
        if (m_instance)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }
    void print()
    {
        std::cout << "print test" << std::endl;
    }
private:
    CSingleton() {}
    CSingleton & operator=(const CSingleton & );
    CSingleton(const CSingleton &) ;
private:
    static CSingleton * m_instance;
    static std::mutex m_mt;
};

CSingleton * CSingleton::m_instance = nullptr;
std::mutex CSingleton::m_mt;

//C++11
class CSingleton
{
public:
	CSingleton() = delete;
    virtual ~CSingleton() = delete;
	   
    CSingleton & operator=(const CSingleton & ) = delete;
    CSingleton(const CSingleton &) = delete;
    static CSingleton & getInstance()
    {
        static CSingleton m_instance;
        return m_instance;
    }
    void print()
    {
        std::cout << "print test" << std::endl;
    }
};

//C++11 template
template<typename T>
class CSingleton
{
public:
    CSingleton() = delete;
    virtual ~CSingleton() = delete;
    CSingleton(const CSingleton&) = delete;
    CSingleton& operator=(const CSingleton&) = delete;

    template<typename... Args>
    static T& getInstance(Args&&... args)
    {
        static T t{ std::forward<Args>(args)... };
        return t;
    }
};

#define SINGLETON(class_name) \
public: \
friend class CSingleton<class_name>; \
using singleton = CSingleton<class_name>; \
private: \
virtual ~class_name() {} \
class_name(const class_name&) = delete; \
class_name& operator=(const class_name&) = delete; \
public: 
