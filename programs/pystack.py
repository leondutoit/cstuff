
# a minimal stack

def push(stack, item):
    stack.append(item)
    print "pushed", item
    return stack

def pop(stack):
    top_item = stack.pop()
    print "popped", top_item
    return stack

def peek(stack):
    top_item = stack[len(stack) - 1]
    print "peeking", top_item

def main():
    stack = []
    stack = push(stack, 5)
    stack = push(stack, 10)
    peek(stack)
    stack = pop(stack)
    peek(stack)

if __name__ == '__main__':
    main()
