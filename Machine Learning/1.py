    #     # Picking the best probabilities frequency according to its parent head and output
    #     # ?? Need discussion with shahid
    # for freq in frequencies:
    #     highestProbParam = ""
    #     highestProb = 0
    #     for param in totalFreq:
    #         try:
    #             if(Y[freq][param] > highestProb):
    #                 highestProb = Y[freq][param]                    
    #                 highestProbParam = param
    #         except:
    #             continue
            
# probabilities = {}
# # e.g P(Outlook = Rain | Yes)
# for parent, frequencies in X.items():
#     for freq in frequencies:
#         result[parent][freq] = 

        

# print(total)

# for attributes in Y.items():
#     print(attributes)
        
# # Calculate Probabilities of all the instances and combine them
# for attributes in Y.items():
#     for key, value in attributes[1].items():
#         if total[attributes[0]] > 0 and value > 0:
#             result[key] *= (value/total[attributes[0]])

# # Multiply the probabilities with the probability of maximum occurence
# totalRows = len(df)
# strongestCase = 0
# strongestCaseKey = ""
# for key in result:
#     result[key] *= (total[key]/totalRows)
#     if result[key] > strongestCase:
#         strongestCase = result[key]
#         strongestCaseKey = key

# print(f'The strongest case is: {strongestCaseKey} with probability of {strongestCase}')    