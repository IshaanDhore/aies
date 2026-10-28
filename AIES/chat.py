# Import libraries
from newspaper import Article
import random
import string
import nltk
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity
import numpy as np
import warnings

warnings.filterwarnings('ignore')

# Download punkt package
nltk.download('punkt', quiet=True)
nltk.download('punkt_tab', quiet=True)

# Input article
article = Article(
    'https://sloanreview.mit.edu/article/why-ai-demands-a-new-breed-of-leaders/'
)

article.download()
article.parse()
article.nlp()

corpus = article.text

# Giving tokens
text = corpus
sentence_list = nltk.sent_tokenize(text)

# Create bot response
def bot_response(user_input):
    user_input = user_input.lower()
    sentence_list.append(user_input)

    cm = CountVectorizer().fit_transform(sentence_list)
    similarity_scores = cosine_similarity(cm[-1], cm).flatten()

    # Sort indices by similarity score 
    # [-1] is the user prompt itself (score 1.0), so the best match is [-2]
    sorted_indices = similarity_scores.argsort()
    best_match_index = sorted_indices[-2]

    if similarity_scores[best_match_index] == 0.0:
        bot_response_text = " I apologize, I don't understand."
    else:
        bot_response_text = " " + sentence_list[best_match_index]

    # Remove the user input from the corpus so it doesn't build up
    sentence_list.remove(user_input)

    return bot_response_text

# Create a function to return random responses to users greeting
def greeting_response(text):
    text = text.lower()

    # Bot greetings response
    bot_greetings = ["hi", "hey", "hello", "hola"]
    user_greetings = ["hi", "hey", "hello", "hola", "greetings"]

    for word in text.split():
        if word in user_greetings:
            return random.choice(bot_greetings)

# Start chatbot
print("Doc Bot: I am a bot for your services. I will answer your questions.")

exit_list = ['exit', 'see you later', 'bye', 'quit', 'break']

while True:
    user_input = input("You: ").lower()

    if user_input in exit_list:
        print("Doc Bot: Chat with you later!")
        break
    else:
        if greeting_response(user_input) is not None:
            print("Doc Bot:", greeting_response(user_input))
        else:
            print("Doc Bot:", bot_response(user_input))

# python chat.py