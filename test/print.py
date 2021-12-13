for base in ["t1e4", "t1e5", "t1e6", "t1e7"]:
    for i in ["serial", "parallel"]:
        if i == "parallel":
            for j in [7, 10, 13]:
                with open(f"data/{base}_stdout_{j}_{i}.txt", "r") as f:
                    st = f.read()
                    print(f"data/{base}_stdout_{j}_{i}.txt", float(st[28:][:-1]))
        else:
            with open(f"data/{base}_stdout_{i}.txt", "r") as f:
                st = f.read()
                print(f"data/{base}_stdout_{i}.txt", float(st[28:][:-1]))
    
    for i in [2, 3, 4]:
        fname = f"data/{base}_stdout_{i}_parallel_hybrid.txt"
        with open(fname, "r") as f:
            st = f.read()
            print(fname, float(st[28:][:-1]))
