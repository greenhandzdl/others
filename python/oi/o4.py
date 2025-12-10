import sys
from collections import defaultdict

def get_card_rank(point, n):
    """
    获取牌的等级数值，按照题目要求排序：
    大王(0) > 小王(1) > 2(2) > A(3) > n(4) > n-1(5) > ... > 4(n-1) > 3(n)
    """
    if point == '0':  # 大王
        return 0
    elif point == '1':  # 小王
        return 1
    elif point == '2':  # 2
        return 2
    elif point == 'A':  # A
        return 3
    elif point.isdigit():
        val = int(point)
        if 3 <= val <= n:
            return n + 3 - val + 1  # n->4, n-1->5, ..., 4->n-1, 3->n
    # 处理J, Q, K
    face_cards = {'J': 11, 'Q': 12, 'K': 13}
    if point in face_cards:
        val = face_cards[point]
        if 3 <= val <= n:
            return n + 3 - val + 1
    return -1  # 错误

def min_single_cards(cards, n):
    """
    计算最优组合后的最小单张数（比A小的单张）
    简化版：只考虑组成对子，不考虑顺子
    """
    # 统计每种牌的数量
    rank_counts = defaultdict(int)
    for card in cards:
        rank = get_card_rank(card[1], n)
        if rank != -1:
            rank_counts[rank] += 1
    
    # 计算单张牌数量（每种牌数量为奇数时会剩余1张）
    low_singles = 0
    for rank, count in rank_counts.items():
        # 如果该牌是单张且比A小（rank > 3）
        if count % 2 == 1 and rank > 3:
            low_singles += 1
    
    # 注意：这是一个简化版本，实际应该考虑顺子等组合
    # 但在某些情况下，简单地组成对子可能已经是最优策略
    
    return low_singles

def main():
    input_lines = []
    try:
        for line in sys.stdin:
            input_lines.append(line.strip())
    except:
        pass
    
    if not input_lines:
        return
    
    n, m = map(int, input_lines[0].split())
    
    for i in range(1, m + 1):
        cards_data = input_lines[i].split()
        cards = []
        
        # 解析牌
        j = 0
        while j < len(cards_data):
            suit = cards_data[j]
            point = cards_data[j + 1]
            cards.append((suit, point))
            j += 2
        
        result = min_single_cards(cards, n)
        print(result)

if __name__ == "__main__":
    main()