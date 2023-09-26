// This file is merely a rough guideline for you. You should create additional
//  test cases to make sure that your implementation behaves correctly
//
// Now that you have learned unit testing with Catch and basic C++, I suggest
//  writing your own unit tests for each function!
//
// Remember: Test with multiple value (V) types!
// (but we'll only test with string K types)

#include "MyUnorderedMap.h"

int main()
{
    std::string my_id;
    get_identity(my_id);
    std::cout <<  my_id << std::endl;

    MyUnorderedMap<std::string, int> unordered_map_obj;

    unordered_map_obj["key6"] = 3;
    unordered_map_obj.insert(MyPair<std::string, int>("aoeu", 2));
    unordered_map_obj["key5"] = 5;
    unordered_map_obj["key3"] = 2;
    unordered_map_obj.at("key5") = 37;

    const MyPair<std::string, int> *temp = unordered_map_obj.find("key5");
    cout << temp->first << " " << temp->second << endl;

    cout << (unordered_map_obj.find("key5") == nullptr) << endl;
    unordered_map_obj.erase("key5");
    cout << (unordered_map_obj.find("key5") == nullptr) << endl;

    MyUnorderedMap<std::string, int> unordered_map_obj2(unordered_map_obj);

    MyUnorderedMap<std::string, int> unordered_map_obj3;
    unordered_map_obj3 = unordered_map_obj2 = unordered_map_obj;

    unordered_map_obj2.print();
    cout << "Size is: " << unordered_map_obj2.size() << endl;
    cout << "Count for key3 is: " << unordered_map_obj2.count("key3") << endl
         << endl;

    unordered_map_obj.clear();

    unordered_map_obj.print();
    cout << "Size is: " << unordered_map_obj.size() << endl;
    cout << "Count for key3 is: " << unordered_map_obj2.count("key3") << endl
         << endl;

    try
    {
        unordered_map_obj.at("key5") = 6;
    }
    catch(const std::out_of_range &e)
    {
        cout << e.what();
    }

    MyUnorderedMap<std::string, int> virus_tree;

    return 0;
}
