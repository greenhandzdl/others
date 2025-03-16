import numpy as np

def input_vector():
    """输入向量"""
    # 获取用户输入并按空格分割
    vector_input = input("请输入向量(用空格分隔各个分量，如: 1 2 3): ")
    # 将输入字符串转换为浮点数列表
    vector = [float(x) for x in vector_input.split()]
    return np.array(vector)

def main():
    print("请输入第一个向量:")
    v1 = input_vector()
    
    print("\n请输入第二个向量:")
    v2 = input_vector()
    
    # 检查维度是否相同
    if len(v1) != len(v2):
        print("错误：两个向量维度不相同！")
        return
    
    # 计算内积
    dot_product = np.dot(v1, v2)
    print(f"\n内积结果: {dot_product}")
    
    # 如果是三维向量，计算外积
    if len(v1) == 3:
        cross_product = np.cross(v1, v2)
        print(f"外积结果: {cross_product}")
    else:
        print("注意：外积只能在三维向量间计算")

if __name__ == "__main__":
    main()
