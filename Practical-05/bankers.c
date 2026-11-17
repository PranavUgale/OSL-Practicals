# PR5: Regression Techniques (CO2, CO3)
# Linear Regression and Polynomial Regression on California Housing Dataset

# Step 1: Import Required Libraries

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.datasets import fetch_california_housing
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures, StandardScaler
from sklearn.pipeline import make_pipeline
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score


# Step 2: Load the Dataset

housing = fetch_california_housing(as_frame=True)
df = housing.frame

print("Dataset shape:", df.shape)
print(df.head())


# Step 3: Select Features and Target

X = df[["MedInc"]]
y = df["MedHouseVal"]


# Step 4: Train-Test Split

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)


# Step 5: Linear Regression

lin_model = LinearRegression()

lin_model.fit(X_train, y_train)

y_pred_lin = lin_model.predict(X_test)


# Step 6: Polynomial Regression (Degree 3)

poly_model = make_pipeline(
    PolynomialFeatures(degree=3),
    StandardScaler(),
    LinearRegression()
)

poly_model.fit(X_train, y_train)

y_pred_poly = poly_model.predict(X_test)


# Step 7: Evaluation Function

def evaluate(y_true, y_pred, name):

    mse = mean_squared_error(y_true, y_pred)
    mae = mean_absolute_error(y_true, y_pred)
    r2 = r2_score(y_true, y_pred)

    print(f"\n{name} Performance:")
    print(f"  MSE : {mse:.4f}")
    print(f"  MAE : {mae:.4f}")
    print(f"  R2  : {r2:.4f}")

    return mse, mae, r2


# Step 8: Evaluate Both Models

lin_scores = evaluate(y_test, y_pred_lin, "Linear Regression")

poly_scores = evaluate(y_test, y_pred_poly, "Polynomial Regression (deg=3)")


# Step 9: Comparison Table

comparison = pd.DataFrame(
    {
        "Model": ["Linear Regression", "Polynomial Regression"],
        "MSE": [lin_scores[0], poly_scores[0]],
        "MAE": [lin_scores[1], poly_scores[1]],
        "R2 Score": [lin_scores[2], poly_scores[2]]
    }
)

print("\nComparison Table:\n", comparison)


# Step 10: Visualization

X_range = pd.DataFrame({
    "MedInc": np.linspace(
        X["MedInc"].min(),
        X["MedInc"].max(),
        300
    )
})

y_range_lin = lin_model.predict(X_range)

y_range_poly = poly_model.predict(X_range)


plt.figure(figsize=(8, 5))

plt.scatter(
    X_test["MedInc"],
    y_test,
    s=8,
    alpha=0.3,
    label="Actual data"
)

plt.plot(
    X_range["MedInc"],
    y_range_lin,
    color="red",
    label="Linear fit"
)

plt.plot(
    X_range["MedInc"],
    y_range_poly,
    color="green",
    label="Polynomial fit (deg=3)"
)

plt.xlabel("Median Income")
plt.ylabel("Median House Value")

plt.title("Linear vs Polynomial Regression - California Housing")

plt.legend()
plt.tight_layout()

plt.savefig("regression_comparison.png", dpi=150)

plt.show()