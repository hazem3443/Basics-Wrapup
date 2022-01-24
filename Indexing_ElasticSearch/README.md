# ElasticSearch

to understand Elasticsearch we need to know more about [Indexing](Indexing) operation and how we can handle indexing in
our database engine

Elasticsearch is a distributed, free and open search and analytics engine for all types of data, including textual, numerical, geospatial, structured, and unstructured. Elasticsearch is built on Apache Lucene and was first released in 2010 by Elasticsearch N.V. (now known as Elastic). Known for its simple REST APIs, distributed nature, speed, and scalability, Elasticsearch is the central component of the Elastic Stack, a set of free and open tools for data ingestion, enrichment, storage, analysis, and visualization. Commonly referred to as the ELK Stack (after Elasticsearch, Logstash, and Kibana), the Elastic Stack now includes a rich collection of lightweight shipping agents known as Beats for sending data to Elasticsearch.

# What is Elasticsearch used for?  

The speed and scalability of Elasticsearch and its ability to index many types of content mean that it can be used for a number of use cases:

* Application search
* Website search
* Enterprise search
* Logging and log analytics
* Infrastructure metrics and container monitoring
* Application performance monitoring
* Geospatial data analysis and visualization
* Security analytics
* Business analytics

# How does Elasticsearch work?
Raw data flows into Elasticsearch from a variety of sources, including logs, system metrics, and web applications. Data ingestion is the process by which this raw data is parsed, normalized, and enriched before it is indexed in Elasticsearch. **Once indexed in Elasticsearch**, users can run complex queries against their data and use aggregations to retrieve complex summaries of their data. From Kibana, users can create powerful visualizations of their data, share dashboards, and manage the Elastic Stack.

elasticSearch stack consists of three main stacks around ElasticSearch or tools or modules you can use

* Logstash
* Kibana 
* X-pack

# What is Logstash/Beats used for?

Logstash, one of the core products of the Elastic Stack, is used to aggregate and process data and send it to Elasticsearch. Logstash is an open source, server-side data processing pipeline that enables you to ingest data from multiple sources simultaneously and enrich and transform it before it is indexed into Elasticsearch.

# What is Kibana used for?
Kibana is a data visualization and management tool for Elasticsearch that provides real-time histograms, line graphs, pie charts, and maps. Kibana also includes advanced applications such as Canvas, which allows users to create custom dynamic infographics based on their data, and Elastic Maps for visualizing geospatial data.

# What is X-pack?

it is a paid add-on offered by **elastic.co** which offers things like security and alerting and monitoring and reporting features like that, it also contains some of the more advanced features such as machine learning and graph exploration so you can see that with x-pack elasticsearch become a real compatitor for much more complex and heavyweight systems like flink and spark but that's another piece of the elastic stack when we talk about this larger ecosystem also there is a **free parts of x-pack** like **the monitoring framework** that will let you quickly visualize what's going on with your cluster and what's your CPU utilization, system load, how much memory do I have available things like that, which helps you know the health of your cluster

# Why use Elasticsearch?
**Elasticsearch is fast**. Because Elasticsearch is built on top of **Lucene**, it excels at full-text search. Elasticsearch is also a near real-time search platform, meaning the latency from the time a document is indexed until it becomes searchable is very short — typically one second. As a result, Elasticsearch is well suited for time-sensitive use cases such as security analytics and infrastructure monitoring.

**Elasticsearch is distributed by nature**. The documents stored in Elasticsearch are distributed across different containers known as shards, which are duplicated to provide redundant copies of the data in case of hardware failure. The distributed nature of Elasticsearch allows it to scale out to hundreds (or even thousands) of servers and handle petabytes of data.

**Elasticsearch comes with a wide set of features**. In addition to its speed, scalability, and resiliency, Elasticsearch has a number of powerful built-in features that make storing and searching data even more efficient, such as data rollups and index lifecycle management.

**The Elastic Stack simplifies data ingest**, visualization, and reporting. Integration with Beats and Logstash makes it easy to process data before indexing into Elasticsearch. And Kibana provides real-time visualization of Elasticsearch data as well as UIs for quickly accessing application performance monitoring (APM), logs, and infrastructure metrics data.

# What programming languages does Elasticsearch support?
Elasticsearch supports a variety of languages and official clients are available for:

* Java
* JavaScript (Node.js)
* Go
* .NET (C#)
* PHP
* Perl
* Python
* Ruby

Elasticsearch provides a comprehensive and powerful set of **REST APIs** for performing tasks such as checking cluster health, performing CRUD (Create, Read, Update, and Delete) and search operations against indices, and executing advanced search operations such as filtering and aggregations.

[Now let's Get started with ElasticSearch](ElasticSearch)