'''
    Variables: 𝐷𝐽, SO, 𝐸𝑇, 𝐾𝐸, 𝑈𝐺 , 𝑇𝐴, 𝑅𝑊, 𝐵𝑈
    Domains: 𝐷𝑖 = red; green; blue
    Constraints: adjacent regions must have different colours
'''
import networkx as nx # For Graph Layout
import matplotlib.pyplot as plt # For drawing/visualizing graphs on screen

G = nx.DiGraph()# Graph type using networkx

numberOfNodes = 0
nodesList = []
nodeEdges = []
domains = ['red', 'green', 'blue'] # Red, Green, Blue

def initializeVariables():
    global numberOfNodes, nodesList, nodeEdges
    f = open("CSP.txt", "r")
    numberOfNodes = int(f.readline())
    nodesList = list(f.readline().split(' '))
    nodesList[len(nodesList)-1] = nodesList[len(nodesList)-1].strip()
    while True:
        data = f.readline()
        if data ==  '':
            break
        edge = data.split(' ')
        edge[len(edge)-1] = edge[len(edge)-1].strip()
        nodeEdges.append(edge)

def generateGraph(solution):
    global G, nodeEdges
    colors = []
    for state, color in solution.items():
        G.add_node(state)# Adding a node
        colors.append(color)
    for edge in nodeEdges: 
        G.add_edge(edge[0], edge[1])# Linking nodes
    pos = nx.spring_layout(G) # Setting layout

    nx.draw_networkx_nodes(G, pos) # Drawing nodes
    nx.draw_networkx_labels(G, pos) # Drawing labels
    nx.draw(G, pos, \
    node_size=1200, node_color=colors, linewidths=0.25, \
    font_size=10, font_weight='bold', with_labels=True, arrows=False)
    plt.show()


class Variable():
    def __init__(self, node, domain):
        self.node = node
        self.domain = domain

class Constraint():
    def __init__(self, edges): # Storing the edges
        # print(variables)
        self.edges = edges

    ''' Function to check if the neighbors have the same domain values '''
    def check(self, values):
        # print(values)
        if len(values) == 0: # That means there are no values thus no constraints
            return True
        v = None
        for val in values: # Assigns a single domain to the variable
            if v is None:
                v = val
            elif val == v: # Checks if the domain is already present returns false
                return False
        return True # If the domain is assigned and has no conflicts it returns true

# Returns a sub set of d with only the items whose key is in the keys array
# e.g d = {BU: R, RW: G}
#     keys = [BU, RW]  
def filterDictionary(d, keys):
    return {k: v for (k, v) in d.items() if k in keys}


# Filtering the values from the dictionaries
# d.items() = [BU: R]
# v = R
def dictionaryToArray(d):
    return [v for (k, v) in d.items()]


''' Merges the two sets[Elimintates the same sets and combines the different sets] '''
def union(d1, d2):
    d = d1.copy()
    d.update(d2)
    return d

class Problem():
    def __init__(self):
        self.variables = []
        self.constraints = []

    def addVariable(self, variable):
        self.variables.append(variable)

    def addConstraint(self, constraint):
        self.constraints.append(constraint)
        # for item in self.constraints:
        #     print(item.variables)
        # print(self.constraints[0].variables)

    def checkConsistency(self, assignment):
        for constraint in self.constraints:
            # Filtering the dictionary with just the matching node names
            relevantValues = filterDictionary(assignment, constraint.edges)
            '''
                Calling Check function to
                check if the neighbors have the same domain value
            '''
            if not constraint.check(dictionaryToArray(relevantValues)): 
                return False
        return True
    
    def find(self, assignment, variables):
        # print(assignment)
        vars = variables.copy()  # because it is passed by reference, we need to create a local copy
        if len(vars) == 0: # If there are no variables left return the assignment
            return [assignment]

        var = vars.pop() # Popping variables that are to be visited
        results = []
        for option in var.domain: # Taking out the available domain options i.e from [R, G, B]
            #print((assignment, {var.node: option}))
            # Eliminating repition and appending the different sets
            newAssignment = union(assignment, {var.node: option})
            ''' 
                 Now performing constraint satisfaction
                 Where we will be adding those assignment in to the final result
                 which donot have a conflict      
            '''
            if self.checkConsistency(newAssignment):
                '''
                    If there are no conflicts in neighbors domain values,
                    further proceed and recursively call this functions
                '''
                res = self.find(newAssignment, vars) 
                results += res
        return results

    def getSolutions(self):
        return self.find({}, self.variables.copy())

initializeVariables()
problem = Problem()

for node in nodesList:
    problem.addVariable(Variable(node, domains))

for edge in nodeEdges: 
    problem.addConstraint(Constraint(edge))

solution = problem.getSolutions()[0]
print(solution)
generateGraph(solution)