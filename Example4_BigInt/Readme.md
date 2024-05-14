# instructions
This example how you could test your own class using CAT library. You should read previous examples if you haven't.

## Codes explained
The BigInt class implmented a class that could add two integers, even if they are very big and can not represent by primitive int type. I don't know why but the professors seem to like this assignment very much because I encountered this homework several times.

There are several techniques used in this examples:

1. In order to do the testing without any error, you need to overload two operators, operator== and operator<<, just like example 2. You should read that example if you haven't.

2. You could group test cases even if one signle test function with variable name confliction. The myth lies in the {}.

## Suggestions
You could add some more cases to observe what will happen.