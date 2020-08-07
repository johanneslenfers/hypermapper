# simple filter test

constraint = "x % 2 == 0"
constraint2 = "1024 % x == 0"
constraint3 = "x % y == 0"
constraint4 = "1024 % x3 == 0"
constraint5 = "1024 % x4 == 0"
inputSize = 1024
name = "x4"

# define filter function
def isPowerOfTwo(a):
    if(a % 2):
        return True
    else:
        return False


y = 3

def constraintWrapper2(parameter):
    # x = parameter
    # result = eval(constraint3, {'y': y}, locals())
    result = eval(constraint5, {}, {name: parameter})
    return result

# def constraintWrapper(parameter):
#     if(eval(str(parameter) + constraint + "==0")):
#         print("valid")
#         return True
#     else:
#         print("not valid")
#         return False
#

print("welcome to a simple filter test")

test = [1,2,3,4,5,6,7,8,9]
print("test: " + str(test))

# result = list(filter(lambda v: not constraintWrapper(v), test))
result = list(filter(constraintWrapper2, test))
print("result: " + str(result))

# for i in test:
# print("test " + str(i) + ": " + str(constraintWrapper(i)))
# print("result: " + str(constraintWrapper2(2)))
# print("result: " + str(constraintWrapper2(3)))
# def constraintWrapper(parameter):
#     x = parameter
#     result = eval(self.constraint, {}, locals())
#     return result
#
#
# result = list(filter(constraintWrapper, self.values_list))


# print("dynamic variable test")
# name = "x3"
# {name: parameter}
# result = eval(constraint3, {'y': y}, locals())
