
export APP=gim
export APPNAME=即时通讯
export NAMESPACE=gim
export VERSION=1.0
export LICENSE=/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/LICENSE

export ARCHETYPE=APPBASE领域驱动框架

export JAR=/Volumes/EXPORT/opt/modelbase-studio-4.0/lib/protosys-plugin-modelbase-4.1-shaded.jar
export OUTPUT_ROOT=/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/gen
export MODELBASE_ROOT=/Volumes/EXPORT/opt/modelbase-studio-4.0/data/archetypes/APPBASE@C-1.0

export MODEL=\
/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/spec/GIM-Proto.modelbase\;/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/spec/GIM.modelbase\;

export DEPENDENT_MODELS=\



export ARTIFACT=$APP

export PROJECT_ROOT=$OUTPUT_ROOT/$ARTIFACT

export MODEL_PROJECT_ROOT=$PROJECT_ROOT

# PREREQUISITES: QUERY, COMMAND, EVENT AND GUIDBASE


#
# *MODEL*
#

export MODEL=\
/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/spec/GIM-Proto.modelbase\;/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/spec/GIM.modelbase\;

export TEMPLATE_ROOT=$MODELBASE_ROOT/c-appbase+db+ws-1.0

java -jar $JAR \
--model=$MODEL \
--dependent-model=$DEPENDENT_MODELS \
--template-root=$TEMPLATE_ROOT \
--output-root=$PROJECT_ROOT \
--license=$LICENSE \
--globals=\
\{\
\"application\":\"$APP\",\
\"namespace\":\"$NAMESPACE\",\
\"artifact\":\"$ARTIFACT\",\
\"version\":\"$VERSION\",\
\"description\":\"$APPNAME\"\,\
\"naming\":\"com.doublegsoft.jcommons.programming.c.CConventions\",\
\"language\":\"c\",\
\"imports\":\
\[\],\
\"dependencies\":\
\[\]\
\} 2>&1


#
# 测试输出objc代码
#
export TEMPLATE_ROOT=$MODELBASE_ROOT/objc-poco@library-1.0

java -jar $JAR \
--model=$MODEL \
--dependent-model=$DEPENDENT_MODELS \
--template-root=$TEMPLATE_ROOT \
--output-root=$PROJECT_ROOT \
--license=$LICENSE \
--globals=\
\{\
\"application\":\"$APP\",\
\"namespace\":\"$NAMESPACE\",\
\"artifact\":\"$ARTIFACT\",\
\"version\":\"$VERSION\",\
\"description\":\"$APPNAME\"\,\
\"naming\":\"com.doublegsoft.jcommons.programming.objc.ObjcConventions\",\
\"language\":\"c\",\
\"imports\":\
\[\],\
\"dependencies\":\
\[\]\
\} 2>&1


cd $PROJECT_ROOT/src && for f in *; do mv "$f" "$f.tmp"; mv "$f.tmp" "`echo $f | tr "[:upper:]" "[:lower:]"`"; done

#
# *BUILD*
#

# mvn clean install deploy -f $OUTPUT_ROOT/stdbiz-$APP-model/pom.xml
# mvn clean install deploy -f $OUTPUT_ROOT/stdbiz-$APP-script/pom.xml


