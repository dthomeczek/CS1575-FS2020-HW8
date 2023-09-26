/* A demo of a similar main with std::unordered_map and std::pair
 * Play around with the real one if you are curious.
 */

#include <unordered_map>
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    std::unordered_map<int, std::string> unordered_map_obj;

    unordered_map_obj.insert(std::pair<int, std::string>(3, "h"));
    unordered_map_obj[54].push_back('w');
    unordered_map_obj[34] = "x";
    unordered_map_obj.at(34) = "y";

    auto temp = unordered_map_obj.find(34);
    cout << temp->first << " " << temp->second << endl;

    unordered_map_obj.erase(34);

    std::unordered_map<int, std::string> unordered_map_obj2(unordered_map_obj);

    std::unordered_map<int, std::string> unordered_map_obj3;
    unordered_map_obj3 = unordered_map_obj2 = unordered_map_obj;

    cout << "Size is: " << unordered_map_obj2.size() << endl;
    cout << "Count for 57 is: " << unordered_map_obj2.count(57) << endl << endl;

    unordered_map_obj.clear();

    cout << "Size is: " << unordered_map_obj.size() << endl;
    cout << "Count for 57 is: " << unordered_map_obj.count(57) << endl;

    try
    {
        unordered_map_obj.at(34) = "k";
    }
    catch(const std::out_of_range &e)
    {
        cout << e.what();
    }

    return 0;
}
