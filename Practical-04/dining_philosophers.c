# PR4: Data Preprocessing and EDA (CO2) - Titanic Dataset

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.model_selection import train_test_split


# 1. Load Dataset

df = sns.load_dataset("titanic")

print(df.shape, "\n", df.head())


# 2. Data Cleaning

df = df.drop_duplicates()

df = df.drop(columns=["deck", "embark_town", "alive", "class"])


# 3. Missing Value Handling

df["age"] = df["age"].fillna(df["age"].median())

df["embarked"] = df["embarked"].fillna(df["embarked"].mode()[0])

df = df.dropna()


# 4. Encoding

df["sex"] = LabelEncoder().fit_transform(df["sex"])

df = pd.get_dummies(df, columns=["embarked", "who"], drop_first=True)

df = df.astype({
    c: int for c in df.select_dtypes("bool").columns
})


# 5. Statistical Analysis

print(df.describe())

print(df.corr(numeric_only=True)["survived"].sort_values(ascending=False))


# 6. Visualization - Histograms

df[["age", "fare", "pclass"]].hist(figsize=(10, 6), bins=20)

plt.suptitle("Histograms")

plt.savefig("histograms.png")

plt.show()


# 7. Visualization - Boxplots

plt.figure(figsize=(8, 4))

plt.subplot(1, 2, 1)
sns.boxplot(y=df["age"])
plt.title("Age")

plt.subplot(1, 2, 2)
sns.boxplot(y=df["fare"])
plt.title("Fare")

plt.tight_layout()

plt.savefig("boxplots.png")

plt.show()


# 8. Feature Scaling

num_cols = ["age", "fare", "sibsp", "parch"]

df[num_cols] = StandardScaler().fit_transform(df[num_cols])


# 9. Train-Test Split

X = df.drop(columns=["survived"])

y = df["survived"]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

print("Train:", X_train.shape, "Test:", X_test.shape)