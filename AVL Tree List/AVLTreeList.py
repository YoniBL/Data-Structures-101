
"""A class represnting a node in an AVL tree"""
import random


class AVLNode(object):
    """Constructor, you are allowed to add more fields.

    @type value: str
    @param value: data of your node
    """
    " ### Splitting init to two different cases - Virtual and real nodes ### "
    " ### value and parent are initialized the same for both cases ### "
    " ### children,height and sized are initialized differently ### "
    "@time compleixty : O(1)"

    def __init__(self, value,virtual=0):
        self.virtual = virtual
        self.value = value
        self.parent = None
        if self.isRealNode() == True:
            self.left = AVLNode(None,1)
            self.right = AVLNode(None,1)
            self.left.setParent(self)
            self.right.setParent(self)
            self.size = 1
            self.height = 0
            self.balance_factor = self.calculateBF()

        else:
            self.right = None
            self.left = None
            self.height = -1
            self.size = 0
            self.balance_factor = 0



    """" updating a node, need to update size,height and balance factor - we will need it after changing a tree structure 
    @time compleixty : O(1) """

    def updateNode(self):
        if self.isRealNode() == True:
            if self.isLeaf():
                self.height = 0
                self.balance_factor = 0
                self.size = 1
            else:  ## node has children - atleast one of them has height that >= 0
                self.height = 1 + max(self.right.height, self.left.height)
                self.size = self.left.size + self.right.size + 1
                self.balance_factor = self.calculateBF()
        return None

    """ return balance factor of a node 
    @time complexity O(1) 
    """

    def getBalanceFactor(self):
        return self.balance_factor

    """returns the left child
    @rtype: AVLNode
    @returns: the left child of self, None if there is no left child
    @time complexity : O(1)
    """

    def getLeft(self):
        return self.left

    """returns the right child

    @rtype: AVLNode
    @returns: the right child of self, None if there is no right child
    @time compleixty : O(1) 
    """

    def getRight(self):
        return self.right

    """returns the parent 

    @rtype: AVLNode
    @returns: the parent of self, None if there is no parent
    @time compleixty : O(1) 
    """

    def getSize(self):
        return self.size

    def getParent(self):
        return self.parent

    """return the value

    @rtype: str
    @returns: the value of self, None if the node is virtual
    @time compleixty : O(1) 
    """

    def getValue(self):
        return self.value

    """returns the height

    @rtype: int
    @returns: the height of self, -1 if the node is virtual
    @time compleixty : O(1) 
    """

    def getHeight(self):
        return self.height

    """sets left child

    @type node: AVLNode
    @param node: a node
    @time compleixty : O(1) 
    """

    "### defining node as my child , defining node.parent as me ###"

    def setLeft(self, node):
        self.left = node
        node.setParent(self)
        return None

    """sets right child

    @type node: AVLNode
    @param node: a node
    @time compleixty : O(1) 
    """

    def setRight(self, node):
        self.right = node
        node.setParent(self)
        return None

    """sets parent

    @type node: AVLNode
    @param node: a node
    @time compleixty : O(1) 
    """

    def setParent(self, node):
        self.parent = node
        return None

    """sets value

    @type value: str
    @param value: data
    @time compleixty : O(1) 
    """

    def setValue(self, value):
        self.value = value
        return None

    """sets the balance factor of the node

    @type h: int
    @param h: the height
    @time compleixty : O(1) 
    """

    def setHeight(self, h):
        self.height = h
        return None

    """returns whether self is not a virtual node 

    @rtype: bool
    @returns: False if self is a virtual node, True otherwise.
    @time compleixty : O(1) 
    """

    "### real nodes has values , virtual nodes values are null ###"

    def isRealNode(self):
        return self.virtual != 1

    """
    return True iff node is a leaf
    @time compleixty : O(1) 
    """

    def isLeaf(self):
        if self.left.isRealNode() == False and self.right.isRealNode() == False:
            return True
        return False

    """
    calculates balance factor , 
    @time compleixty : O(1) 
    """

    def calculateBF(self):
        if self.getLeft().isRealNode() and self.getRight().isRealNode():
            return self.left.getHeight() - self.right.getHeight()
        elif self.getLeft().isRealNode() == False and self.getRight().isRealNode():
            return -self.getHeight()
        elif self.getLeft().isRealNode() == True and self.getRight().isRealNode() == False:
            return self.getHeight()
        else:
            return 0


"""
A class implementing the ADT list, using an AVL tree.
"""


class AVLTreeList(object):
    """
    Constructor, you are allowed to add more fields.

    """

    def __init__(self):
        self.size = 0
        self.root = None
        self.firstItem = None
        self.lastItem = None

    # add your fields here

    """returns whether the list is empty

    @rtype: bool
    @returns: True if the list is empty, False otherwise
    size field we'll be maintained by the avl tree's root size field 
     @time complexity O(1)
    """

    def getTreeHeight(self):
        if self.root != None:
            return self.root.getHeight()
        return -1

    def empty(self):
        return self.root == None

    """retrieves the value of the i'th item in the list

    @type i: int
    @pre: 0 <= i < self.length()
    @param i: index in the list
    @rtype: str
    @time compleixty : O(log(n)) 
    using tree select as we've seen in class, i always in range for list size so no worries there 
    @returns: the the value of the i'th item in the list
    """

    def retrieve(self, i):
        if self.root == None:
            return None
        if i < self.length() and i >= 0:
            return self.treeSelect(i + 1).getValue()
        return None

    """inserts val at position i in the list

    @type i: int
    @pre: 0 <= i <= self.length()
    @param i: The intended index in the list to which we insert val
    @type val: str
    @param val: the value we inserts
    @rtype: list
    @returns: the number of rebalancing operation due to AVL rebalancing
    @time compleixty : O(log(n))
    implemented as Danny explained in the video, we insert to a bst using predeccessor , takes log(n) , then fixing upwards,
    going up takes log(n) and rotates takes O(1)

    """

    def insert(self, i, val):
        if i <= self.length() and i >= 0:
            return self.avlTreeInsert(val, i)
        return None

    def append(self, val):
        return self.insert(self.length(), val)

    """deletes the i'th item in the list

    @type i: int
    @pre: 0 <= i < self.length()
    @param i: The intended index in the list to be deleted
    @rtype: int
    @returns: the number of rebalancing operation due to AVL rebalancing
    @time compleixty : O(log(n))
    deleting from a bst as we've seen in class, fixing all the way up same same way as insertion besides adding some cases
    """

    def delete(self, i):
        if i < self.length() and i >= 0:
            return self.avlDelete(i)
        return -1

    """returns the value of the first item in the list

    @rtype: str
    @returns: the value of the first item, None if the list is empty
    we maintain the tree's minimum node as a field  , will represent the first item on the list 
    @time complexity O(1)
    """

    def first(self):
        if self.root != None:
            return self.firstItem.getValue()
        return None

    """returns the value of the last item in the list

    @rtype: str
    @returns: the value of the last item, None if the list is empty
    we maintain the tree's max node as a field , will represent the last item on the list 
    @time complexity O(1)
    """

    def last(self):
        if self.root != None:
            return self.lastItem.getValue()
        return None

    """returns an array representing list 

    @rtype: list
    @returns: a list of strings representing the data structure
    @time compleixty : O(n)
    adding to array every item on list through inorder recursive walk
    """

    def listToArray(self):
        arr = []
        if self.root != None:
            return self.listToArrRecursive(self.getRoot(), arr)
        return arr

    def listToArrRecursive(self, node, arr):
        if node != None:
            self.listToArrRecursive(node.getLeft(), arr)
            if node.isRealNode():
                arr.append(node.getValue())
            self.listToArrRecursive(node.getRight(), arr)
        return arr

    """returns the size of the list 

    @rtype: int
    @returns: the size of the list
    @time complexity O(1)
    """

    def length(self):
        if self.root != None:
            return self.root.size
        return 0

    """sort the info values of the list

    @rtype: list
    @returns: an AVLTreeList where the values are sorted by the info of the original list.
    @time compleixty : O(nlogn)
    with O(n) time we can have the list as an array with list to arr , sorting takes nlogn using quicksort as seen in
    introduction to cs1001 - no need to explain further more
    then inserting n to a new tree . 
    because we insert n items in a row ( serial insertion ), and we always insert to the maximum aka last item in the list
    we have seen the amortized cost of the series is O(n) , therefor it doesnt hurt the time complexity and the total time
    complexity is determined by sorting
    """

    def sort(self):

        if self.root != None:
            def quicksort(lst):
                """ quick sort of lst """
                if len(lst) <= 1:
                    return lst
                else:
                    pivot = random.choice(lst)  # select a random element from list
                    # pivot = lst[0] #for a deterministic quicksort

                    smaller = [elem for elem in lst if elem < pivot]
                    equal = [elem for elem in lst if elem == pivot]
                    greater = [elem for elem in lst if elem > pivot]

                    return quicksort(smaller) + equal + quicksort(greater)

            curr_lst = self.listToArray()
            srted_lst = quicksort(curr_lst)
            srted_tree = AVLTreeList()
            for i in range(len(curr_lst)):
                srted_tree.insert(i, srted_lst[i])
            return srted_tree
        empty_tree = AVLTreeList()
        return empty_tree

    """permute the info values of the list 

    @rtype: list
    @returns: an AVLTreeList where the values are permuted randomly by the info of the original list. ##Use Randomness
    @time compleixty : (O(n))
    almost the same as sort - we take the array form of the list and shuffle with , shuffle by python is O(n) and gives 
    us our list shuffled in O(n)
    same insertion series to the maximum will cost O(n) therefore everything is O(n)
    """

    def permutation(self):
        if self.root != None:
            curr_lst = self.listToArray()
            n = len(curr_lst)
            rnd_tree = AVLTreeList()
            for i in range(n):
                rnd = random.randrange(0, n)
                temp = curr_lst[i]
                curr_lst[i] = curr_lst[rnd]
                curr_lst[rnd] = temp
            for i in range(len(curr_lst)):
                rnd_tree.insert(i, curr_lst[i])
            return rnd_tree
        empty_tree = AVLTreeList()
        return empty_tree

    """concatenates lst to self

    @type lst: AVLTreeList
    @param lst: a list to be concatenated after self
    @rtype: int
    @returns: the absolute value of the difference between the height of the AVL trees joined
    @time compleixty : O(log(n))
    using join trees as seen in the lectures with added fixtures to match it to our list , so it takes O(log(n))
    because total runtime is the same 
    """

    def concat(self, lst):
        my_height = 0
        if self.empty():
            self.firstItem = lst.firstItem
            self.lastItem = lst.lastItem
            self.root = lst.getRoot()
            if lst.empty():
                return 0
            self.size = self.length()
            return abs(-1 - lst.root.height)
        else:
            my_height = self.root.height
            other_height = lst.treeHeight()
            x = self.lastItem
            self.delete(self.length() - 1)
            self.joinTrees(x, lst)
            self.size = self.length()
            if lst.empty() == False:
                return abs(my_height - other_height)
            return abs(my_height - (-1))

    """searches for a *value* in the list

    @type val: str
    @param val: a value to be searched
    @rtype: int
    @returns: the first index that contains val, -1 if not found.
    @time compleixty : O(n)
    going through successors till we find the item if exists, worst case we do successors n times in a row , seen in 
    recitation that will take worst case O(n) when tree is an avl  
    """

    def search(self, val):
        if self.root != None:
            node = self.firstItem
            index = 0
            while node != None:
                if node.getValue() == val:
                    return index
                index += 1
                node = self.successor(node)
        return -1

    """returns the root of the tree representing the list

    @rtype: AVLNode
    @returns: the root, None if the list is empty
    @time complexity O(1)
    """

    def getRoot(self):
        return self.root

    """ methods on trees from now on """
    """returns the location of node in the tree
    @time complexity log(n)
    """

    def treeRank(self, node):
        r = node.getLeft().size + 1
        y = node
        while y != None:
            if y.getParent() != None:
                if y == y.getParent().getRight():
                    r = r + y.getParent().getLeft().size + 1
            y = y.getParent()
        return r

    """ return the k'th item on the tree 
    @time complexity O(logn)
    """

    def treeSelect(self, k):
        return self.selectRec(self.root, k)

    def selectRec(self, node, k):
        r = node.getLeft().size + 1
        if k == r:
            return node
        elif k < r:
            return self.selectRec(node.getLeft(), k)
        else:
            return self.selectRec(node.getRight(), k - r)

    """returns the smallest item on the tree
    @time complexity o(logn)
    """

    def treeMin(self, node):
        while node.getLeft().isRealNode() == True:
            node = node.getLeft()
        return node

    """returns the biggest item on the tree
    @time complexity o(logn)
    """

    def treeMax(self, node):
        while node.getRight().isRealNode() == True:
            node = node.getRight()
        return node

    """returns the successor of node on the tree
    @time complexity o(logn)
    """

    def successor(self, node):
        if node.getRight().isRealNode():
            return self.treeMin(node.getRight())
        y = node.getParent()
        while y != None and node == y.getRight():
            node = y
            y = node.getParent()
        return y

    """returns the predecessor of node on the tree
    @time complexity o(logn)
    """

    def predecessor(self, node):
        if  node.getLeft().isRealNode():
            return self.treeMax(node.getLeft())
        y = node.getParent()
        while y != None and node == y.getLeft():
            node = y
            y = node.getParent()
        return y

    """ deleting from an avl tree the item in the location i, behaving towards first and last items a bit differently
      we're using the fix after deletion function and bst delete 
      time complexity O(log(n))"""

    def avlDelete(self, i):
        node_to_delete = self.treeSelect(i + 1)
        if i == self.length() - 1:
            self.lastItem = self.predecessor(self.lastItem)
        elif self.successor(node_to_delete) == self.lastItem:
            self.lastItem = node_to_delete
        if i == 0:
            self.firstItem = self.successor(self.firstItem)
        parent = self.bstDelete(node_to_delete)
        cnt = self.fixAfterDeletion(parent)
        self.size = self.length()
        return cnt

    """ inserting into a bst as danny tought in the video, will take O(logn) worst case cause our tree is an avl
    @time compleixty : O(log(n))"""

    def treeInsert(self, node, i):
        if self.root == None:  ## if tree is empty
            self.root = node
            self.lastItem = node
            self.firstItem = node
        else:
            if i == self.length():  ## insert last
                self.lastItem.setRight(node)
                self.lastItem = node
            elif i == 0:  ## insert first
                self.firstItem.setLeft(node)
                self.firstItem = node
            else:
                curr = self.treeSelect(i + 1)
                if curr.getLeft().isRealNode() == False:  ## current node at index i has no left child , we make node his predecessor
                    curr.setLeft(node)
                else:  ##current node at i has a left child , we will make node his predecessors successors
                    curr_pred = self.predecessor(curr)
                    curr_pred.setRight(node)

    """ avl insertion , we insert into a bst , then we fix after insertion and count amount of operations we've done 
    @time compleixty :O(log(n))"""

    def avlTreeInsert(self, item, i):
        node = AVLNode(item)
        self.treeInsert(node, i)
        counter = self.fixAfterInsertion(node)
        self.size = self.length()
        return counter

    """ fix after insertion , going up to our parents and fix with rotates nodes with bf = 2 
    @time compleixty : O(log(n)) """

    def fixAfterInsertion(self, node):
        fixing_cnt = 0
        node.updateNode()
        y = node.getParent()
        while y != None:
            y.updateNode()
            if abs(y.getBalanceFactor()) < 2:
                y = y.getParent()
                continue
            else:
                fixing_cnt += self.fixWithRotates(y)
                y = y.getParent()
                continue
        return fixing_cnt

    """ same same as fix after insertion , @time compleixty : O(log(n))"""

    def fixAfterDeletion(self, parent):
        fixing_cnt = 0
        while parent != None:
            parent.updateNode()
            if abs(parent.getBalanceFactor()) < 2:
                parent = parent.getParent()
                continue
            else:
                fixing_cnt += self.fixWithRotates(parent)
                parent = parent.getParent()
                continue
        return fixing_cnt

    """fixing nodes with | bf | = 2 , using the right rotations as explained in class each rotation is just some pointers movement so 
    @time compleixty :O(1) """

    def fixWithRotates(self, node):
        rotations_counter = 0
        if node.getBalanceFactor() == -2:
            if node.getRight().getBalanceFactor() == -1 or node.getRight().getBalanceFactor() == 0:
                self.leftRotation(node)
                rotations_counter += 1
            elif node.getRight().getBalanceFactor() == 1:
                self.rightRotation(node.getRight())
                self.leftRotation(node)
                rotations_counter += 2
        if node.getBalanceFactor() == 2:
            if node.getLeft().getBalanceFactor() == 1 or node.getLeft().getBalanceFactor() == 0:
                self.rightRotation(node)
                rotations_counter += 1
            elif node.getLeft().getBalanceFactor() == -1:
                self.leftRotation(node.getLeft())
                self.rightRotation(node)
                rotations_counter += 2
        return rotations_counter

    """ rightRotation and leftRotation are just rotation functions , 
    time complexity O(1)
    """

    def rightRotation(self, node):
        left_son = node.getLeft()
        node.setLeft(left_son.getRight())
        curr_parent = node.getParent()
        if curr_parent != None:
            if curr_parent.getRight() == node:
                curr_parent.setRight(left_son)
            else:
                curr_parent.setLeft(left_son)
        if curr_parent == None:
            left_son.setParent(None)
        left_son.setRight(node)
        if node == self.root:
            self.root = left_son
        node.updateNode()
        left_son.updateNode()

    def leftRotation(self, node):
        right_son = node.getRight()
        node.setRight(right_son.getLeft())
        curr_parent = node.getParent()
        if curr_parent != None:
            if curr_parent.getRight() == node:
                curr_parent.setRight(right_son)
            else:
                curr_parent.setLeft(right_son)
        if curr_parent == None:
            right_son.setParent(None)
        right_son.setLeft(node)
        if node == self.root:
            self.root = right_son
        node.updateNode()
        right_son.updateNode()

    """ deleting from a bst as tought in class 
    time complexity O(log(n)) cause tree is balanced """

    def bstDelete(self, node):  ## deleting from a bst tree , return's parent of actually deleted node
        if node.isLeaf():  ## if node is a leaf , just remove it , update parent replaced son
            if self.root == node:  ## if we have only one node on tree and we remove it , tree becomes empty
                self.root = None
                self.firstItem = None
                self.lastItem = None
                return None
            parent = node.getParent()
            if parent != None:
                if parent.getRight() == node:
                    parent.setRight(AVLNode(None,1))
                else:
                    parent.setLeft(AVLNode(None,1))
                node.setParent(None)
            return parent

        elif node.isLeaf() == False:  ## if node is not a leaf
            if node.getRight().isRealNode() and node.getLeft().isRealNode() == False:  ## node has only one child , its a right child
                if node == self.root and node.size == 2:  ## tree of size two , we remove the root
                    self.root = node.getRight()
                    self.firstItem = node.getRight()
                    self.lastItem = node.getRight()
                    node.getRight().setParent(None)

                parent = node.getParent()
                if parent != None:
                    if node == parent.getRight():
                        parent.setRight(node.getRight())
                        node.setParent(None)
                    elif node == parent.getLeft():
                        parent.setLeft(node.getRight())
                        node.setParent(None)
                return parent

            elif node.getRight().isRealNode() == False and node.getLeft().isRealNode():  ## node has only one child but its a left child
                parent = node.getParent()
                if parent != None:
                    if node == parent.getRight():
                        parent.setRight(node.getLeft())
                        node.setParent(None)
                    elif node == parent.getLeft():
                        parent.setLeft(node.getLeft())
                        node.setParent(None)
                if node == self.root and node.size == 2:  ## tree of size two , we remove the root
                    self.root = node.getLeft()
                    self.firstItem = node.getLeft()
                    self.lastItem = node.getLeft()
                    node.getLeft().setParent(None)

                return parent

            elif node.getRight().isRealNode() and node.getLeft().isRealNode():  ## node has two children , replace values with successor then delete successor
                succ = self.successor(node)
                new_val = succ.getValue()
                node.setValue(new_val)
                return self.bstDelete(succ)

    """ return trees height , handeling the case tree is empty
    time complexity O(1)"""

    def treeHeight(self):
        if self.root != None:
            return self.root.height
        else:
            return -1

    """ join trees is O(log(n)) implemented the same method we've seen in class ,using the so called x node as our last 
    item from our list 
    time complexity O(log(n))"""

    def joinTrees(self, x, tree2):
        if tree2.empty():
            self.insert(self.length(), x.getValue())
            return None
        elif self.empty():
            tree2.insert(0, x.getValue())
            self.firstItem = tree2.firstItem
            self.lastItem = tree2.lastItem
            self.root = tree2.root
        elif self.getRoot().getHeight() == tree2.getRoot().getHeight():
            x.setLeft(self.getRoot())
            x.setRight(tree2.getRoot())
            x.setParent(None)
            self.root = x

        elif self.getRoot().getHeight() < tree2.getRoot().getHeight():
            curr = tree2.getRoot()
            while curr.getHeight() > self.getRoot().getHeight():
                curr = curr.getLeft()
            parent = curr.getParent()
            x.setRight(curr)
            x.setLeft(self.getRoot())
            parent.setLeft(x)
            self.root = tree2.getRoot()

        else:
            curr = self.getRoot()
            while curr.getHeight() > tree2.getRoot().getHeight():
                curr = curr.getRight()

            parent = curr.getParent()
            x.setRight(tree2.getRoot())
            x.setLeft(curr)
            parent.setRight(x)

        self.lastItem = tree2.lastItem
        x.updateNode()
        if self.getRoot() != x:
            self.fixAfterDeletion(x)

    """done"""

    def printt(self):
        out = ""
        for row in self.printree(self.root):  # need printree.py file
            out = out + row + "\n"
        print(out)

    def printree(self, t, bykey=True):
        # for row in trepr(t, bykey):
        #        print(row)
        return self.trepr(t, False)

    def trepr(self, t, bykey=False):
        if t == None:
            return ["#"]

        thistr = str(t.key) if bykey else str(t.getValue())

        return self.conc(self.trepr(t.left, bykey), thistr, self.trepr(t.right, bykey))

    def conc(self, left, root, right):

        lwid = len(left[-1])
        rwid = len(right[-1])
        rootwid = len(root)

        result = [(lwid + 1) * " " + root + (rwid + 1) * " "]

        ls = self.leftspace(left[0])
        rs = self.rightspace(right[0])
        result.append(ls * " " + (lwid - ls) * "_" + "/" + rootwid *
                      " " + "\\" + rs * "_" + (rwid - rs) * " ")

        for i in range(max(len(left), len(right))):
            row = ""
            if i < len(left):
                row += left[i]
            else:
                row += lwid * " "

            row += (rootwid + 2) * " "

            if i < len(right):
                row += right[i]
            else:
                row += rwid * " "

            result.append(row)

        return result

    def leftspace(self, row):
        # row is the first row of a left node
        # returns the index of where the second whitespace starts
        i = len(row) - 1
        while row[i] == " ":
            i -= 1
        return i + 1

    def rightspace(self, row):
        # row is the first row of a right node
        # returns the index of where the first whitespace ends
        i = 0
        while row[i] == " ":
            i += 1
        return i
