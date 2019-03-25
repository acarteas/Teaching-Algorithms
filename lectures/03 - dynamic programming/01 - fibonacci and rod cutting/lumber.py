def calculate_price(length, mem):

    #handle all base cases
    if length < 6:
        return 0
    if length < 8:
        return 2
    if length < 10:
        return 3
    if length < 12:
        return 4
    if length < 16:
        return 5
    if length < 18:
        return 7
    if length < 20:
        return 9
    if length < 24:
        return 10
    if length == 24:
        return 12
    
    #goal: find max of all possibilities
    prices = [2, 3, 4, 5, 7, 9, 10, 12]
    cuts = [6, 8, 10, 12, 16, 18, 20, 24]

    result = []
    for i in range(len(cuts)):
        cut = cuts[i]
        price = prices[i]

        result_price = 0
        if (length - cut in mem) == False:
            result_price = calculate_price(length - cut, mem)
            mem[length - cut] = result_price
        else:
            result_price = mem[length - cut]
        result.append(result_price + price)
    return max(result)

def calculate_price_bu(length):
    prices = [2, 3, 4, 5, 7, 9, 10, 12]
    cuts = [6, 8, 10, 12, 16, 18, 20, 24]
    best_prices = []
    for i in range(6):
        best_prices.append(0)
    for i in range(len(cuts) - 1):
        for j in range(cuts[i + 1] - cuts[i]):
            best_prices.append(prices[i])
    best_prices.append(12)
    return best_prices

print(calculate_price(1000, {}))
result = calculate_price_bu(50)
print("done")