for base in ["t1e4", "t1e5", "t1e6", "t1e7"]:
    for i in ["serial", "parallel"]:
        if i == "parallel":
            for j in range(2, 25):
                with open(f"data/{base}_stdout_{j}_{i}.txt", "r") as f:
                    st = f.read()
                    print(float(st[28:][:-1]))
        else:
            with open(f"data/{base}_stdout_{i}.txt", "r") as f:
                st = f.read()
                print(float(st[28:][:-1]))
