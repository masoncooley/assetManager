# Documentation for IT Asset Inventory Project




## Draft 2
My first step is to try and implement some of the features suggested to me by my teacher:

> Add Accessor and Mutator Methods in Asset class.  Consider adding these methods for flexibility.  
> 
> It might be useful to provide a constructor that initializes id and name directly so you don't always have to set them manually.
> 
> You have set all the methods in InventoryManager as void for now, but many of them should likely return values, especially those related to asset manipulation.
> 
> Right now, there’s no mention of how assets will be stored. You may want to consider using a container like unordered_map to store your assets efficiently. If you want to keep track of assets by ID, a map would be a good choice. Research for more information.  
> 
> You could extend the validation to ensure that the user doesn't enter invalid data types (e.g., non-integer input). For example, you could use cin.fail() to > catch invalid inputs and prompt the user again.
> 
> Be sure to comment your code and explain the purpose of each class and method. Even though the overall flow of the program is clear, commenting will make it easier for others or yourself in the future to understand the design decisions and functionality.


Apparently I forgot to make the child Asset classes (`Desktop`, `Server`, `Mobile`) inherit from Asset. 
To do this I have to change the class declarations from: 
```
class Desktop
{

}
```

To:
```
class Desktop : public Asset
{
    
}
```


### Generating IDs and Names
Nothing interesting here, I just followed examples from Chapter 3.10 in the textbook for my random numbers.

### Using Smart Pointers with Objects
Smart pointers are described in Chapter 10.13 of the textbook. The premise behind a smart pointer is they are objects that work like pointers. Additionally, they have the ability to automatically delete dynamically allocated memory.

Unique pointers are dynamically allocated objects that are owned by a single pointer.

After research, it's best to have a [*virtual destructor*](https://www.learncpp.com/cpp-tutorial/virtual-destructors-virtual-assignment-and-overriding-virtualization/) on the Asset class since I'm working with inheritance.

`->` is the structure pointer operator, explained in 10.11 of textbook.

### Asset Storage with `unordered_map`
I have no idea what an unordered map is, so I started researching and found [this GeeksForGeeks page](https://www.geeksforgeeks.org/cpp/unordered_map-in-cpp-stl/). 

Essentially an unordered map stores values in key:value form using hashing and as the name implies, there is no sorting. Since I want to track assets mainly by ID, this would work perfectly. The ID can be the key and the `InventoryManager` object can be the value.

I was going to use the `insert()` function for adding new entries to the map, but ["for objects, use of emplace() is preferred for efficiency reasons."](https://www.geeksforgeeks.org/cpp/emplace-vs-insert-c-stl/).
























- [Documentation for IT Asset Inventory Project](#documentation-for-it-asset-inventory-project)
  - [Draft 2](#draft-2)
    - [Generating IDs and Names](#generating-ids-and-names)
    - [Using Smart Pointers with Objects](#using-smart-pointers-with-objects)
    - [Asset Storage with `unordered_map`](#asset-storage-with-unordered_map)
