def calculate_edit_distance(first, second):
    matrix = []

    # construct matrix
    for i in range(len(first) + 1):
        matrix.append([])
        for j in range(len(second) + 1):
            matrix[i].append(0)

    # fill in first row
    for i in range(len(matrix[0])):
        matrix[0][i] = i

    # fill in first column
    for i in range(len(matrix)):
        matrix[i][0] = i

    # compute rest of matrix
    for i in range(1, len(matrix)):
        for j in range(1, len(matrix[i])):

            top_cost = matrix[i - 1][j] + 1
            left_cost = matrix[i][j - 1] + 1
            diagonal_cost = matrix[i - 1][j - 1]

            # add 1 to diagonal if chars don't match
            if(first[i - 1] != second[j - 1]):
                diagonal_cost += 1

            best_choice = min(top_cost, left_cost, diagonal_cost)
            matrix[i][j] = best_choice
    return matrix[len(matrix) - 1][len(matrix[0]) - 1]

if __name__ == '__main__':
   print("dog and frog:", calculate_edit_distance("dog", "frog"))
   print("of and racoon:", calculate_edit_distance("of", "racoon"))
