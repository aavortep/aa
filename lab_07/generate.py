from collections import Counter
A = ""
f = open("orig.txt", "r", encoding="utf8")


def remov_duplicates(words):

	# split input string separated by space
	words = words.split(" ")

	# joins two adjacent elements in iterable way
	for i in range(0, len(words)):
		words[i] = "".join(words[i])

	# now create dictionary using counter method
	# which will have strings as key and their
	# frequencies as value
	UniqW = Counter(words)

	# joins two adjacent elements in iterable way
	s = " ".join(UniqW.keys())

# Driver program
if __name__ == "__main__":
        for words in f:
            words = f.readline()
            remov_duplicates(words)
            A += words

f.close()

remov_duplicates(A)
A = A.split(" ")
fi = open("data.txt","w",encoding="utf8")
for i in range(1500):
        if len(A[i]) > 1:
                fi.write("{} {}\n".format(i+1, A[i]))

fi.close()
