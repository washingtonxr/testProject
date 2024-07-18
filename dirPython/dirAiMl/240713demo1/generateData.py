#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import pandas as pd
import numpy as np
import os
import sys
import torch
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from torch.utils.data import DataLoader, TensorDataset
import torch.nn as nn
import torch.optim as optim

DATA_FILE_NAME = "system_logs.csv"
DATA_FILE_PATH = "dataSource"

def check_arguments():
    print(f"Arguments count: {len(sys.argv)}")
    print(f"Name of the script      : {sys.argv[0]=}")
    print(f"Arguments of the script : {sys.argv[1:]=}")

    try:
        arg = sys.argv[1]
    except IndexError as errorInfo:
        print(f"Error {errorInfo}")
        #raise SystemExit(f"Error {errorInfo}, Usage: {sys.argv[0]} <string_to_reverse>")
    #print(arg[::-1])

    for i, arg in enumerate(sys.argv):
        print(f"Argument {i:>6}: {arg}")

def generate_log_data1(source_path):
    print(f"Source path:{source_path}")

    # Create a sample dataset
    data = {
        'timestamp': [
            '2023-01-01 00:00:00', '2023-01-01 00:01:00', '2023-01-01 00:02:00', 
            '2023-01-01 00:03:00', '2023-01-01 00:04:00', '2023-01-01 00:05:00'
        ],
        'error_code': [
            'E101', 'E102', 'E103', 'E104', 'E101', 'E105'
        ],
        'message': [
            'Initialization successful', 'Connection timeout', 'Data overflow', 
            'Packet loss', 'Initialization successful', 'Unknown error'
        ],
        'label': [
            'normal', 'error', 'error', 'error', 'normal', 'error'
        ]
    }

    # Create a DataFrame
    df = pd.DataFrame(data)

    # Save to CSV
    csv_path = file_input = os.path.join(source_path, DATA_FILE_PATH, DATA_FILE_NAME)
    df.to_csv(csv_path, index=False)
    print(csv_path)

def generate_log_data2(source_path):
    # Create a sample dataset with 1 million rows
    n_samples = 1000

    timestamps = pd.date_range('2023-01-01', periods=n_samples, freq='T').astype(str)
    error_codes = np.random.choice(['E101', 'E102', 'E103', 'E104', 'E105'], n_samples)
    messages = np.random.choice(['Initialization successful', 'Connection timeout', 'Data overflow', 'Packet loss', 'Unknown error'], n_samples)
    labels = np.random.choice(['normal', 'error'], n_samples)

    # Create a DataFrame
    large_data = pd.DataFrame({
        'timestamp': timestamps,
        'error_code': error_codes,
        'message': messages,
        'label': labels
    })

    # Save to CSV
    import shutil
    folder_path= os.path.join(source_path, DATA_FILE_PATH)
    if not os.path.exists(folder_path):
        os.mkdir(folder_path)
    else:
        if os.path.exists(folder_path):
            shutil.rmtree(folder_path) # remove the directory and its contents
            os.mkdir(folder_path) # recreate the directory

    csv_path = file_input = os.path.join(source_path, DATA_FILE_PATH, DATA_FILE_NAME)
    large_data.to_csv(csv_path, index=False)
    print(csv_path)

def gather_prepare_data(dataFile):
    # Load the data
    data = pd.read_csv(dataFile)

    # Display the first few rows of the data
    print(data.head())
    return data

def clean_and_prepare_data(data):
    # Check if CUDA is available
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    # Example feature extraction (converting categorical to numerical)
    label_encoder = LabelEncoder()
    data['error_code_encoded'] = label_encoder.fit_transform(data['error_code'])

    # Splitting data into features and labels
    X = data[['error_code_encoded']]
    y = label_encoder.fit_transform(data['label'])

    # Split data into train and test sets
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    # Convert to PyTorch tensors
    X_train_tensor = torch.tensor(X_train.values, dtype=torch.float32)
    y_train_tensor = torch.tensor(y_train, dtype=torch.long)
    X_test_tensor = torch.tensor(X_test.values, dtype=torch.float32)
    y_test_tensor = torch.tensor(y_test, dtype=torch.long)

    # Create DataLoader
    train_dataset = TensorDataset(X_train_tensor, y_train_tensor)
    test_dataset = TensorDataset(X_test_tensor, y_test_tensor)
    train_loader = DataLoader(train_dataset, batch_size=2, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=2, shuffle=False)

    return train_loader, test_loader, device

def develop_the_model(device):
    print(f"device = {device}")
    class LogClassifier(nn.Module):
        def __init__(self):
            super(LogClassifier, self).__init__()
            self.fc1 = nn.Linear(1, 16)
            self.fc2 = nn.Linear(16, 32)
            self.fc3 = nn.Linear(32, 16)
            self.fc4 = nn.Linear(16, 2)  # Assuming binary classification (normal/error)
            self.relu = nn.ReLU()
            self.softmax = nn.Softmax(dim=1)

        def forward(self, x):
            x = self.relu(self.fc1(x))
            x = self.relu(self.fc2(x))
            x = self.relu(self.fc3(x))
            x = self.softmax(self.fc4(x))
            return x

    if device != "cpu":
        # Initialize the model
        model = LogClassifier()
    else:
        # Initialize the model and move it to the GPU
        model = LogClassifier().to(device)
    return model

def training_the_model(model, train_loader):
    # Loss function and optimizer
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=0.001)

    # Training loop
    num_epochs = 20
    for epoch in range(num_epochs):
        model.train()
        running_loss = 0.0
        for i, (inputs, labels) in enumerate(train_loader):
            optimizer.zero_grad()
            outputs = model(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
            running_loss += loss.item()
        print(f'Epoch [{epoch+1}/{num_epochs}], Loss: {running_loss/len(train_loader)}')

def evaluating_the_model(model):
    # Evaluation
    model.eval()
    correct = 0
    total = 0
    with torch.no_grad():
        for inputs, labels in test_loader:
            outputs = model(inputs)
            _, predicted = torch.max(outputs.data, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()

    print(f'Accuracy: {100 * correct / total}%')

if __name__ == "__main__":
    check_arguments()
    path_file_current = os.path.dirname(os.path.realpath(__file__))
    generate_log_data2(path_file_current)

    data_file = os.path.join(path_file_current, DATA_FILE_PATH, DATA_FILE_NAME)
    data = gather_prepare_data(data_file)
    train_loader, test_loader, device = clean_and_prepare_data(data)
    model = develop_the_model(device)
    training_the_model(model, train_loader)
    evaluating_the_model(model)

    print("Done")

# End of this file
