# PR9: SVM vs Random Forest vs AdaBoost
# Cross Validation + Grid Search (Digits dataset)

# Import required libraries

from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split, cross_val_score, GridSearchCV
from sklearn.preprocessing import StandardScaler
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier, AdaBoostClassifier
from sklearn.metrics import accuracy_score


# Step 1: Load the dataset

X, y = load_digits(return_X_y=True)

print("Dataset shape:", X.shape)


# Step 2: Split into training and testing data (75% / 25%)

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.25, random_state=42, stratify=y
)


# Step 3: Scale the features (needed for SVM)

scaler = StandardScaler()

X_train = scaler.fit_transform(X_train)

X_test = scaler.transform(X_test)


# Step 4: Create the three models with default settings

models = {
    "SVM": SVC(),
    "Random Forest": RandomForestClassifier(random_state=42),
    "AdaBoost": AdaBoostClassifier(random_state=42)
}


# Step 5: Parameter grids for Grid Search

grids = {
    "SVM": {
        "C": [0.1, 1, 10],
        "gamma": ["scale", 0.01, 0.001],
        "kernel": ["linear", "rbf"]
    },

    "Random Forest": {
        "n_estimators": [50, 100, 200],
        "max_depth": [None, 5, 10]
    },

    "AdaBoost": {
        "n_estimators": [50, 100, 200],
        "learning_rate": [0.1, 0.5, 1.0],
        "estimator": [
            DecisionTreeClassifier(max_depth=d)
            for d in (1, 2, 3)
        ]
    }
}


# Step 6: BEFORE tuning - Cross validation and test accuracy

print("\n----- BEFORE OPTIMIZATION -----")

before = {}

for name, model in models.items():

    cv_score = cross_val_score(
        model, X_train, y_train, cv=5
    ).mean()

    model.fit(X_train, y_train)

    test_acc = accuracy_score(
        y_test, model.predict(X_test)
    )

    before[name] = (cv_score, test_acc)

    print(
        f"{name:14s} CV accuracy = {cv_score:.4f}  "
        f"Test accuracy = {test_acc:.4f}"
    )


# Step 7: AFTER tuning - Grid Search with 5-fold cross validation

print("\n----- AFTER OPTIMIZATION (Grid Search) -----")

after = {}

for name, model in models.items():

    grid = GridSearchCV(
        model, grids[name], cv=5
    )

    grid.fit(X_train, y_train)

    test_acc = accuracy_score(
        y_test, grid.predict(X_test)
    )

    after[name] = (grid.best_score_, test_acc)

    best = grid.best_params_.copy()

    if "estimator" in best:
        best["estimator"] = (
            f"DecisionTree(max_depth={best['estimator'].max_depth})"
        )

    print(
        f"{name:14s} CV accuracy = {grid.best_score_:.4f}  "
        f"Test accuracy = {test_acc:.4f}"
    )

    print("   Best parameters:", best)


# Step 8: Compare before and after

print("\n----- COMPARISON (Test Accuracy) -----")

print(
    f"{'Model':14s} {'Before':>8s} "
    f"{'After':>8s} {'Gain':>8s}"
)

for name in models:

    b, a = before[name][1], after[name][1]

    print(
        f"{name:14s} {b:8.4f} {a:8.4f} {a-b:+8.4f}"
    )