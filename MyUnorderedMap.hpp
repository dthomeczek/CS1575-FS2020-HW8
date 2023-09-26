// Implement all of your MyUnorderedMap functions and other related functions
//  here 
void get_identity(std::string &my_id)
{
    my_id = "djtpfr";
}

template <typename K, typename V>
int MyUnorderedMap<K,V>::hash(const K &key) const
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
    {
        sum = sum + int(key[i]);
    }
    return sum % reserved_size;
}

template <typename K, typename V>
MyUnorderedMap<K,V>::MyUnorderedMap()
{
    m_data = nullptr;
    data_size = 0;
    reserved_size = 0;
}

template <typename K, typename V>
MyUnorderedMap<K,V>::~MyUnorderedMap()
{
    delete[] m_data;
}

template <typename K, typename V>
MyUnorderedMap<K,V>::MyUnorderedMap(const MyUnorderedMap<K,V> &source)
{
    data_size = source.data_size;
    reserved_size = source.reserved_size;
    if (source.m_data == nullptr)
    {
        m_data = nullptr;
    }
    else
    {
        for (int i = 0; i < reserved_size; i++)
        {
            m_data[i] = source.m_data[i];
        }
    }
}

template <typename K, typename V>
MyUnorderedMap<K,V> & MyUnorderedMap<K,V>::operator=(const MyUnorderedMap<K,V> &source)
{
    data_size = source.data_size;
    reserved_size = source.reserved_size;
    if (source.m_data == nullptr)
    {
        m_data = nullptr;
        return *this;
    }
    for (int i = 0; i < reserved_size; i++)
    {
        m_data[i] = source.m_data[i];
    }
    return *this;
}

template <typename K, typename V>
V & MyUnorderedMap<K,V>::at(const K &key)
{
    if (empty() == true)
    {
        throw std::out_of_range("MyUnorderedMap::at\n");
    }
    int hashed = hash(key);
    if (m_data[hashed].first == key)
    {
        return m_data[hashed].second;
    }
    if ((((data_size + 1) * 3) / 5) >= reserved_size)
    {
        reserve(reserved_size * 2);
    }
    for (int i = 0; i < reserved_size; i++)
    {
        if (m_data[i].first == key)
        {
            return m_data[i].second;
        }
    }
    throw std::out_of_range("MyUnorderedMap::at\n");
}

template <typename K, typename V>
V & MyUnorderedMap<K,V>::operator[](const K &key)
{
    if (empty() == true)
    {
        m_data = new MyPair<K,V>[2];
        m_data[0] = MyPair<K,V>(key);
        m_data[1] = MyPair<K,V>("empty", 0);
        reserved_size = 2;
        data_size = 1;
        return m_data[0].second;
    }
    int hashed = hash(key);
    if (m_data[hashed].first == key)
    {
        return m_data[hashed].second;
    }
    for (int i = 0; i < reserved_size; i++)
    {
        if (m_data[i].first == key)
        {
            return m_data[i].second;
        }
    }
    if ((((data_size + 1) * 3) / 5) >= reserved_size)
    {
        reserve(reserved_size * 2);
    }
    data_size += 1;
    for (int k = 0; k < reserved_size; k++)
    {
        if (m_data[k].second == 0)
        {
            m_data[k] = MyPair<K,V>(key);
            return m_data[k].second;
        }
    }
    delete[] m_data;
}

template <typename K, typename V>
bool MyUnorderedMap<K,V>::empty() const
{
    if ((data_size == 0) || m_data == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename K, typename V>
int MyUnorderedMap<K,V>::size() const
{
    return data_size;
}

template <typename K, typename V>
void MyUnorderedMap<K,V>::clear()
{
    data_size = 0;
    reserved_size = 0;
    delete[] m_data;
    m_data = nullptr;
}

template <typename K, typename V>
void MyUnorderedMap<K,V>::insert(const MyPair<K,V> &init_pair)
{
    if (empty() == true)
    {
        m_data = new MyPair<K,V>[2];
        m_data[0] = MyPair<K,V>(init_pair.first, init_pair.second);
        m_data[1] = MyPair<K,V>("empty", 0);
        return;
    }
    if ((((data_size + 1) * 3) / 5) >= reserved_size)
    {
        reserve(reserved_size * 2);
    }
    int hashed = hash(init_pair.first);
    if (m_data[hashed].second == 0)
    {
        m_data[hashed] = init_pair;
    }
    else if (m_data[hashed].first == init_pair.first)
    {
        m_data[hashed].second += 1;
    }
    else
    {
        for (int i = 0; i < reserved_size; i++)
        {
            if (m_data[i].second == 0)
            {
                m_data[i] = init_pair;
            }
        }
    }
    data_size += 1;
    return;
}

template <typename K, typename V>
void MyUnorderedMap<K,V>::erase(const K &key)
{
    if (empty() == true)
    {
        return;
    }
    if (((data_size - 1) * 10) <= reserved_size)
    {
        reserve((reserved_size * 3) / 10);
    }
    int hashed = hash(key);
    if (m_data[hashed].first == key)
    {
        m_data[hashed] = MyPair<K,V>("empty",0);
        return;
    }
    for (int i = 0; i < reserved_size; i++)
    {
        if (m_data[i].first == key)
        {
            m_data[i] = MyPair<K,V>("empty",0);
            return;
        }
    }
}

template <typename K, typename V>
MyPair<K,V> * MyUnorderedMap<K,V>::find(const K &key) const
{
    int hashed = hash(key);
    MyPair<K,V> *ret_val;
    if (m_data[hashed].first == key)
    {
        return &m_data[hashed];
    }
    else
    {
        for (int i = 0; i < reserved_size; i++)
        {
            if (m_data[i].first == key)
            {
                return &m_data[i];
            }
        }
    }
    return nullptr;
}

template <typename K, typename V>
void MyUnorderedMap<K,V>::print() const
{
    for (int i = 0; i < reserved_size; i++)
    {
        if (m_data[i].second != 0)
        {
            std::cout << "[" << m_data[i].first << "]=" << m_data[i].second << std::endl;
        }
    }
    return;
}

template <typename K, typename V>
int MyUnorderedMap<K,V>::count(const K &key) const
{
    int hashed = hash(key);
    if (m_data[hashed].first == key)
    {
        return 1;
    }
    for (int i = 0; i < reserved_size; i++)
    {
        if (m_data[i].first == key)
        {
            return 1;
        }
    }
    return 0;
}

template <typename K, typename V>
void MyUnorderedMap<K,V>::reserve(int new_cap)
{
    if (m_data == nullptr)
    {
        m_data = new MyPair<K,V>[2];
        m_data[0] = MyPair<K,V>("empty",0);
        m_data[1] = MyPair<K,V>("empty",0);
        return;
    }
    MyPair<K,V> *temp = m_data;
    m_data = new MyPair<K,V>[new_cap];
    int old_reserved_size = reserved_size;
    reserved_size = new_cap;
    for (int i = 0; i < new_cap; i++)
    {
        m_data[i] = MyPair<K,V>("empty", 0);
    }
    int hashed;
    for (int k = 0; k < old_reserved_size; k++)
    {
        if (temp[k].second != 0)
        {
            insert(temp[k]);
        }
    }
    delete[] temp;
    return;
}


void get_virus_frequency(MyUnorderedMap<std::string, int> &in_tree)
{
    std::string w = "";
    char c;
    while (std::cin.get(c))
    {
        if ((c >=65 && c <= 90) || ( c >= 97 && c <= 12) || ( c >= 48 && c <= 57) || c == 95)
        {
            w.push_back(c);
        }
        else if (!w.empty())
        {
            if (w.size() >= 5)
            {
                for (int i = 0; i < w.size() - 4; ++i)
                {
                    if ((w[i] == 86 || w[i] == 118) && (w[i + 1] == 73 || w[i + 1] == 105) && (w[i + 2] == 82 || w[i + 2] == 114) && (w[i + 3] == 85 || w[i + 3] == 117) && (w[i + 4] == 83 || w[i + 4] == 115))
                    {
                        if (in_tree.count(w) == 0)
                        {
                            in_tree.insert(MyPair<std::string,int>(w,1));
                        }
                        else
                        {
                            in_tree[w]++;
                        }
                    }
                }
            }
        }
        w = "";
    }
    return;
}
