class ListNode:
    def __init__(self, val=0):
        self.val = val
        self.next = None

def create_linked_list(arr):
    dummy = ListNode()
    current = dummy
    for num in arr:
        current.next = ListNode(num)
        current = current.next
    return dummy.next

def linked_list_to_list(head):
    result = []
    current = head
    while current:
        result.append(current.val)
        current = current.next
    return result

def insert_node(head, k, d):
    dummy = ListNode()
    dummy.next = head
    current = dummy
    if k == 0:
        new_node = ListNode(d)
        new_node.next = dummy.next
        dummy.next = new_node
        return dummy.next
    for _ in range(k):
        if not current.next:
            return head
        current = current.next
    new_node = ListNode(d)
    new_node.next = current.next
    current.next = new_node
    return dummy.next

def delete_node(head, k):
    if k == 0:
        return head
    dummy = ListNode()
    dummy.next = head
    current = dummy
    for _ in range(k - 1):
        if not current.next:
            return head
        current = current.next
    if current.next:
        current.next = current.next.next
    return dummy.next

if __name__ == "__main__":
    import sys
    input = sys.stdin.read
    data = input().splitlines()
    n = int(data[0].strip())
    arr = list(map(int, data[1].strip().split()))
    m = int(data[2].strip())
    operations = [list(map(int, line.split())) for line in data[3:]]
    head = create_linked_list(arr)
    for op in operations:
        if op[0] == 0:
            _, k, d = op
            head = insert_node(head, k, d)
        elif op[0] == 1:
            _, k = op
            head = delete_node(head, k)
    result = linked_list_to_list(head)
    print(" ".join(map(str, result)) + " ")