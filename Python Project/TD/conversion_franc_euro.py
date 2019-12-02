def convert_franc_to_euro(somme_franc):
	conversion_franc_to_euro_const = 6.55957
	somme_euro = somme_franc / conversion_franc_to_euro_const
	return somme_euro

francs = float(input("enter a franc float value"))
print(convert_franc_to_euro(francs))