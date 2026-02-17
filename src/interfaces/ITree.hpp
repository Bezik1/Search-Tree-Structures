template <typename T>
class ITree
{
    virtual ~ITree() {};

    virtual void add(T value) = 0;
    virtual void add(int idx, T el) = 0;
    virtual void clear() = 0;
    
    virtual boolean contains(T el) const = 0;
};