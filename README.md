# Details on Implementation

The following are points in the implementation that I would like to draw attention to.
These may not be issues but offer some explanation for some decisions. (These may not be necessary).

## Comments 

* All the TODO block comments have been rewritten to more closely follow the doxygen commenting style using ///.
* While the relative order of the functions should be maintained, apologies if they are not in the right order after 
refactoring, although I have tried to take care to fix any thing that was in the wrong order. Some of my own functions have been included near to where they are used or are "thematically" similar.
* Whilst trying to maintain the order of the functions, they have been grouped together logically. For example 
all the functions dealing the "JSON" are under a big, clearly visible JSON comment, as if it was a subtitle.
This "subtitle" comment and similar comments are present throughout each implemented file.
* While this may not be expected, I personally think this has good style - or at least has been beneficial to me.  

## JSON

* Where appropriate, the classes contain a `to_json()` and `from_json()`, which follows the style as in the nlohmann json library.
Due to this, these have a slightly different style to any other function, i.e. these are snake case, while everything else is camel case.
Also, these are more meant to be used with classes with default constructors, according to the documentation. However, this 
is only applicable to Date here. Otherwise, these are manually used.

## Shared Pointers

* Category and ExpenseTracker objects have maps with values that are `shared_ptr`s. This makes copying the objects easier without destroying the Item or Category objects they contain. 

## Update Action

* I don't believe the case that when updating a category `--category oldIdentifier:newIdentifier`, the new identifier may match an existing
category has been specified (maybe I am wrong). This implementation will use the addCategory() function's handling of this situation.

