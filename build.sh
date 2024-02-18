
export APP=jim
export APPNAME=即时通讯
export NAMESPACE=jim
export VERSION=1.0
export LICENSE=/Users/christian/export/local/works/sdic.com/juno/03.Development/jim/LICENSE

export ARCHETYPE=APPBASE领域驱动框架

export JAR=/Users/christian/export/opt/modelbase-studio-4.0/lib/protosys-plugin-modelbase-4.1-shaded.jar
export OUTPUT_ROOT=/Users/christian/export/local/works/sdic.com/juno/03.Development/jim
export MODELBASE_ROOT=/Users/christian/export/opt/modelbase-studio-4.0/data/archetypes/APPBASE@C-1.0

export MODEL=\
/Users/christian/export/local/works/sdic.com/juno/03.Development/jim/JIM.modelbase\;

export DEPENDENT_MODELS=\



export ARTIFACT=$APP

export PROJECT_ROOT=$OUTPUT_ROOT/$ARTIFACT

export MODEL_PROJECT_ROOT=$PROJECT_ROOT

# PREREQUISITES: QUERY, COMMAND, EVENT AND GUIDBASE


#
# *MODEL*
#

export MODEL=\
/Users/christian/export/local/works/sdic.com/juno/03.Development/jim/JIM.modelbase\;

export TEMPLATE_ROOT=$MODELBASE_ROOT/c-appbase+model-1.0

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

export TEMPLATE_ROOT=$MODELBASE_ROOT/c-appbase+lua-1.0

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

export TEMPLATE_ROOT=$MODELBASE_ROOT/c-appbase+mongoose-1.0

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


cd $PROJECT_ROOT/src && for f in *; do mv "$f" "$f.tmp"; mv "$f.tmp" "`echo $f | tr "[:upper:]" "[:lower:]"`"; done

#
# *BUILD*
#

# mvn clean install deploy -f $OUTPUT_ROOT/stdbiz-$APP-model/pom.xml
# mvn clean install deploy -f $OUTPUT_ROOT/stdbiz-$APP-script/pom.xml


cp -f $OUTPUT_ROOT/$ARTIFACT/script/$NAMESPACE/sql.lua /Users/christian/export/local/projs/goodmanager/dev/rel/latest/script/gm/
cp -f $OUTPUT_ROOT/$ARTIFACT/db/setup-database.sql /Users/christian/export/local/projs/goodmanager/dev/rel/latest/db/

