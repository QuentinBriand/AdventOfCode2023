##
## EPITECH PROJECT, 2023
## AdventOfCode2023
## File description:
## main
##


EXAMPLE_FILENAME = "resources/Day07/example"
FIRST_FILENAME = "resources/Day07/longInput"

possibleHands = {
    'five of a kind': (5,),
    'four of a kind': (4,),
    'full house': (3, 2),
    'three of a kind': (3,),
    'two pair': (2, 2),
    'one pair': (2,),
    'high card': (1,1,1,1)
}

part1_orders = ['A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2']
part2_orders = ['A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J']
possible_hands_in_order = ['five of a kind', 'four of a kind', 'full house', 'three of a kind', 'two pair', 'one pair', 'high card']

def checkHand(hand, useJokers=False):
    count_dict = {i: hand.count(i) for i in hand}
    count_values = [count_dict[i] for i in count_dict if i != 'J' or not useJokers]
    discarded = []
    jokerCount = 0
    if useJokers and 'J' in count_dict:
        jokerCount = count_dict['J']
    tmpJokerCount = jokerCount
    if useJokers and jokerCount == 5:
        return 'five of a kind'

    for possibleHandName in possibleHands:
        validCount = 0
        cards = possibleHands[possibleHandName]
        for card in cards:
            for cardWithJoker in [card - i for i in range(tmpJokerCount + 1) if card - i >= 0]:
                if cardWithJoker in count_values:
                    count_values.remove(cardWithJoker)
                    discarded.append(cardWithJoker)
                    validCount += 1
                    tmpJokerCount = 0
        if validCount == len(cards):
            return possibleHandName
        else:
            count_values.extend(discarded)
            discarded = []
            tmpJokerCount = jokerCount

    return 'invalid hand'


def getScore(hand):
    handType = checkHand(hand, useJokers=True)
    # print(hand)
    # print(handType)
    # print()
    if handType == 'invalid hand':
        return -1
    else:
        res = [possible_hands_in_order.index(handType)] + [part2_orders.index(i) for i in hand]
        return res


if __name__ == '__main__':
    with open(FIRST_FILENAME) as f:
        lines = [line.strip() for line in f.readlines()]

    hands = []

    for line in lines:
        hand, bid = line.split(' ')
        bid = int(bid)
        hands.append((hand, bid))

    sortedHands = sorted(hands, key=lambda x: getScore(x[0]), reverse=True)
    totalWinnings = [(idx + 1) * bid for idx, (_, bid) in enumerate(sortedHands)]
    print(sum(totalWinnings))
